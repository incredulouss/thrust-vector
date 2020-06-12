//y axis is upward servo . and clockwise direction is negative
//X axis is downward servo . and clockwise direction is negative

#include <Wire.h>
#include <Kalman.h> 
#include <Servo.h>
#include "pins.h"

void setup()
{
  Serial.begin(9600);
  delay(100);
  servoInIt();
  startSen();
  pyroInit();
  led_buzz_Init();
  runAll();
//  call();
//   calibrateServo();
  // printImuVal(3);
   //delay(500);
   //buzzCal( 1000 , 1000 , 2);
  // calibrateServo(); 
  // buzzCal( 1000 , 1000 , 2);
 //rotateServo(refAngleX , 110,'Y');   
    //rotateServo(refAngleX , 30,'X');  
  buzzCal( 1000 , 1000 , 1);
}


void loop() 
{ 
  Pid();
  //digitalWrite(pyro1,HIGH);
  //firePyro(1);
 // buzzCal( 1000 , 1000 , 25);
  //int a = rollError();
  // rollPid();
 //  printImuVal(3);
//   delay(500);
//   rotateServo(refAngleX , refAngleX+10,'X');    
//   printImuVal(3);
//   delay(10000);                           
}
