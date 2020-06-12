#define servoSpeed 10
#define testAngle 20
#define servoCalibrationFactor 2

void servoInIt()
{
myservoX.attach(5); 
myservoY.attach(6);

pinMode(ledB,OUTPUT);
servoAllign(1000);
}
void servoAllign(int delayAllign)
{
  myservoX.write(refAngleX);               
  myservoY.write(refAngleY);
  delay(delayAllign);  
}
//press 1 to move X axis 5 degree in neg diretion and press 2 to move it 5 degree in positive direction 
//press 3 to move Y axis 5 degree in neg diretion and press 4 to move it 5 degree in positive direction
//press 5 to end this function
void calibrateServo()
{
  digitalWrite(blue , HIGH);
  delay(500);
  char check = 'a';
  char m=0;
  Serial.println(check);
 while(check == 'a')
 {
     if (Serial.available() > 0) {
      m = Serial.read();
      switch(m)
      {   
      case 'B': refAngleX +=servoCalibrationFactor;
                Serial.println(m);
                myservoX.write(refAngleX);
                break;

      case 'b': refAngleX -=servoCalibrationFactor;
                Serial.println(m);
                myservoX.write(refAngleX);
                break;

      case 'C': refAngleY +=servoCalibrationFactor;
                 Serial.println(m);
                 myservoY.write(refAngleY);
                 break;
                 
       case 'c': refAngleY -=servoCalibrationFactor;
                 Serial.println(m);
                 myservoY.write(refAngleY);
                 break;

       case 'G': check = 'f';
                 break;
      }
    }
}}
void servoCali(int noOfTimes)
{
  digitalWrite(ledB ,1);
  servoAllign(1000);
    for(int i =0 ; i<noOfTimes ; i++)
  {
    rotateServo(refAngleX , refAngleX+testAngle,'X');       
    rotateServo(refAngleX+testAngle ,refAngleX-testAngle,'X');                             
    rotateServo(refAngleX-testAngle ,refAngleX,'X'); 
  //delay(500);
    rotateServo(refAngleY ,refAngleY+testAngle,'Y'); 
    rotateServo(refAngleY+testAngle ,refAngleY-testAngle,'Y'); 
    rotateServo(refAngleY-testAngle ,refAngleY,'Y'); 
}
  digitalWrite(ledB ,0);
  servoAllign(100);
}
void rotateServo(int startAngle ,int endAngle,char cordinate)
{
  char dir;
  if(startAngle<=endAngle)
  dir = '+';
  else dir = '-';
  //Serial.println(dir);
  if(dir == '+')
  {
     if(cordinate == 'X')
     {
       for (int pos = startAngle; pos <= endAngle; pos += servoSpeed) {
        myservoX.write(pos);           
        delay(25);                       
      }}
      else if(cordinate == 'Y')
      {
        for (int pos = startAngle; pos <= endAngle; pos += servoSpeed) { 
        myservoY.write(pos);              
        delay(25);                       
      }}
  }
  if(dir == '-')
  {
      if(cordinate == 'X')
     {
       for (int pos = startAngle; pos >= endAngle; pos -= servoSpeed) {
        myservoX.write(pos);           
        delay(25);                       
      }}
      else if(cordinate == 'Y')
      {
        for (int pos = startAngle; pos >= endAngle; pos -= servoSpeed) { 
        myservoY.write(pos);              
        delay(25);                       
      }}
  }
}
