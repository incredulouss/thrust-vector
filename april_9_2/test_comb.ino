  int normalizeRoll =0 ;
  int normalizePitch = 0;
void test()
{

  int rollX = (int)rollVal();
  int pitchY = (int)pitchVal()+4;
  normalizeRoll = constrain(map(rollX,-70,70,minAngleX,maxAngleX),40,100);
  normalizePitch = constrain(map(pitchY,-70,70,minAngleY,maxAngleY),40,100);
  Serial.print(normalizeRoll);
  Serial.print( ',' );
  Serial.println(normalizePitch);
//  rotateServo(rollX ,normalizeRoll,'X');
  //rotateServo(pitchY ,normalizePitch,'Y');
  myservoX.write(normalizeRoll); 
  myservoY.write(normalizePitch); 
   delay(15);
  //rotateSudden(normalizeRoll , 'X');
  ///rotateSudden(mormalizePitch , 'Y');
  
  
}
