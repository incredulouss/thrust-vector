
#define RKp 1
#define RKd 0
#define RKi 0

#define PKp 1
#define PKd 0
#define PKi 0

int rollError()
{
  int rollError = 0;
  int rollLastError = 0;
  float rollIntegralError=0;

  while(1)
  {
    receiveVal();
    Serial.print(rolly);
    Serial.print(" , ");
    rollError = imuRollReference - rolly;
    rollIntegralError +=rollError;
    int servoCorrection = RKp * rollError + RKd * (rollError - rollLastError) + RKi * rollIntegralError;
    rollLastError =rollError;
    int servoAngle = refAngleX - servoCorrection;
    servoAngle = constrain(servoAngle,minAngleX,maxAngleX);

    Serial.print(rollError);
    Serial.print(" , ");
    Serial.print(servoAngle);
    Serial.print(" , ");
    return servoAngle;  
  }
}

void rollPid()
{
  int rollAng = rollError();
  myservoX.write(rollAng);
  delay(20); 
}

int pitchError()
{
  int pitchError = 0;
  int pitchLastError = 0;
  float pitchIntegralError=0;

 while(1)
  {
    receiveVal();
    Serial.print(polly);
    Serial.print(" , ");
   pitchError = imuPitchReference - polly;
   pitchIntegralError +=pitchError;
   int servoCorrection = PKp * pitchError + PKd * (pitchError - pitchLastError) + PKi * pitchIntegralError;
   pitchLastError =pitchError;
   int servoAngle = refAngleY + servoCorrection;
   servoAngle = constrain(servoAngle,minAngleY,maxAngleY);
   
   Serial.print(pitchError);
   Serial.print(" , ");
   Serial.println(servoAngle);
   return servoAngle;  
  }
}

void Pid()
{
  int rollAng = rollError();
  int pitchAng = pitchError();
  myservoY.write(pitchAng);
  myservoX.write(rollAng);
//  delay(5); 
}
