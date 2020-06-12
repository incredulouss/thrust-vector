/*IN mobile APP press following buttons to activate diffrent functions
 *Press B to activate servo testing (off of switch 2)
 *Press C to activate servo manual calibration (On of switch 2)
   *To move X axis servo press B (off of switch 2)
   *To move Y axis servo press C (off of switch 3)
   *To exit press G (off of switch 8)
   
 *Press D to check pyro (off of switch 4)
   *press A to D for 1 to 4 pyro
   *press G to exit (off of switch 8)

 *Press E to check Buzzer and led 
 */
 

void runAll()
{
  digitalWrite(pink , HIGH);
  delay(500);
  char m=0;
  Serial.println(state);
   while(state == 'a')
 {
     if (Serial.available() > 0) {
     m = Serial.read();
       Serial.println(m);
  switch(m)
  {
    case 'C': digitalWrite(blue,HIGH);
              Serial.println("calibrate");   //press D to end the calibrate servo
              calibrateServo();
              digitalWrite(blue,LOW);
              break;
              
    case 'B': Serial.println("call");
              call();
              break; 

    case 'D': Serial.println("pyroFire");
              pyrofire();
              break;

    case 'E': Serial.println("launch");
              Pid();
              break;           
              
    case 'H': state = 'f';
              break;              
  }}
  }
  digitalWrite(pink , LOW);
}
