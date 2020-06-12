
void startSen()
{
   Wire.begin();
#if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
#else
  TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
#endif

  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
  while (i2cWrite(0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode

  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
    Serial.print(F("Error reading sensor"));
    while (1);
  }

  delay(100); // Wait for sensor to stabilize

  /* Set kalman and gyro starting angle */
  while (i2cRead(0x3B, i2cData, 6));
  accX = (int16_t)((i2cData[0] << 8) | i2cData[1]);
  accY = (int16_t)((i2cData[2] << 8) | i2cData[3]);
  accZ = (int16_t)((i2cData[4] << 8) | i2cData[5]);

#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif

  kalmanX.setAngle(roll); // Set starting angle
  kalmanY.setAngle(pitch);
  gyroXangle = roll;
  gyroYangle = pitch;
  compAngleX = roll;
  compAngleY = pitch;

  timer = micros();
  errorRoll = rollVal();
  errorPoll = pitchVal();
  delay(100);
//  Serial.print(errorRoll);
//  Serial.print("  ,  ");
//  Serial.println(errorPoll);
}
void calRaw()
{
   while (i2cRead(0x3B, i2cData, 14));
  accX = (int16_t)((i2cData[0] << 8) | i2cData[1]);
  accY = (int16_t)((i2cData[2] << 8) | i2cData[3]);
  accZ = (int16_t)((i2cData[4] << 8) | i2cData[5]);
  tempRaw = (int16_t)((i2cData[6] << 8) | i2cData[7]);
  gyroX = (int16_t)((i2cData[8] << 8) | i2cData[9]);
  gyroY = (int16_t)((i2cData[10] << 8) | i2cData[11]);
  gyroZ = (int16_t)((i2cData[12] << 8) | i2cData[13]);

  dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros(); 
  gyroXrate = gyroX / 131.0; // Convert to deg/s
  gyroYrate = gyroY / 131.0; // Convert to deg/s
  gyroZrate = gyroZ /131.0;  // Convert to deg/s
}
double rollVal()
{
  calRaw();
  #ifdef RESTRICT_PITCH 
   roll  = atan2(accY, accZ) * RAD_TO_DEG;
   #else
   roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
   #endif
   
  #ifdef RESTRICT_PITCH
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
    kalmanX.setAngle(roll);
    compAngleX = roll;
    kalAngleX = roll;
    gyroXangle = roll;
  } else
    kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleX) > 90)
    gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
  #endif

  //  gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
  gyroXangle += kalmanX.getRate() * dt;
  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll;
  
  if (gyroXangle < -180 || gyroXangle > 180)
  gyroXangle = kalAngleX;

  return roll;
}
double pitchVal()
{
  calRaw();
     // It is then converted from radians to degrees
  #ifdef RESTRICT_PITCH
  pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
  #else 
    pitch = atan2(-accX, accZ) * RAD_TO_DEG;
  #endif
    gyroYrate = gyroY / 131.0; // Convert to deg/s

  #ifdef RESTRICT_PITCH
    if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
        kalmanY.setAngle(pitch);
        compAngleY = pitch;
        kalAngleY = pitch;
        gyroYangle = pitch;
  } else
        kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleY) > 90)
        gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
        kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
  #endif

 //  gyroYangle += gyroYrate * dt;  //Calculate without using filter
  gyroYangle += kalmanY.getRate() * dt;

  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch; //Complimentary filter

  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalAngleY;
    return pitch;
}
double yawVal()
{
  calRaw();

  #ifdef RESTRICT_PITCH
  yaw = atan(accZ / sqrt(accX*accX + accZ*accZ)) * RAD_TO_DEG;
  #else 
  yaw = atan2(accX, accY) * RAD_TO_DEG;
  #endif
 #ifdef RESTRICT_PITCH
    if ((yaw < -90 && kalAngleZ > 90) || (pitch > 90 && kalAngleY < -90)) {
        kalmanZ.setAngle(yaw);
        compAngleZ = yaw;
        kalAngleZ = yaw;
        gyroZangle = yaw;
  } else
        kalAngleZ = kalmanZ.getAngle(yaw, gyroZrate, dt); // Calculate the angle using a Kalman filter

  if (abs(kalAngleZ) > 90)
        gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
        kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
  #endif

 //  gyroYangle += gyroYrate * dt;  //Calculate without using filter
  gyroZangle += kalmanZ.getRate() * dt;

  compAngleZ = 0.93 * (compAngleZ + gyroZrate * dt) + 0.07 * yaw; //Complimentary filter

  if (gyroZangle < -180 || gyroZangle > 180)
    gyroZangle = kalAngleZ;
    return yaw;
}
void receiveVal()
{
  rolly = rollVal()-(errorRoll);
  polly = pitchVal()-(errorPoll);
}

void printImuVal(int a)
{
  /* value of a
   *  1. raw value
   *  2. roll value
   *  3. rolly and polly
   *  4. Yaw value
   *  5. polly
   *  6. temperature
   */
  switch(a)    
  {
    case 1 :   calRaw();
               Serial.print(accX); Serial.print("\t");
               Serial.print(accY); Serial.print("\t");
               Serial.print(accZ); Serial.print("\t");

               Serial.print(gyroX); Serial.print("\t");
               Serial.print(gyroY); Serial.print("\t");
               Serial.println(gyroZ); Serial.print("\t");
               break;    

    case 2 :   receiveVal();
               Serial.print(rolly); Serial.print("\t");
               Serial.print(gyroXangle); Serial.print("\t");
               Serial.print(compAngleX); Serial.print("\t");
               Serial.println(kalAngleX); Serial.print("\t");
               break;

   case 3 :    receiveVal();
               Serial.print(rolly); Serial.print("\t");
               Serial.print(polly); Serial.println("\t");
               break; 

    case 4 :   int yolla = yawVal();
               Serial.print(yolla); Serial.print("\t");
               Serial.print(gyroZangle); Serial.print("\t");
               Serial.print(compAngleZ); Serial.print("\t");
               Serial.println(kalAngleZ); Serial.print("\t");
               break;

    case 5 :   receiveVal();
               Serial.print(polly); Serial.println("\t");
               break;

    case 6 :   temperature = (double)tempRaw / 340.0 + 36.53;
               Serial.print(temperature); Serial.println("\t");
               break;

}
}
