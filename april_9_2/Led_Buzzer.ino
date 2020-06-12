
void led_buzz_Init()
{
    pinMode(buzzer, OUTPUT);
    pinMode(blue,OUTPUT);
    pinMode(orange,OUTPUT);
    pinMode(pink,OUTPUT);  
}
void buzzStart(int freqHz)
{
  tone(buzzer, freqHz); 
}
void buzzStop()
{
  noTone(buzzer);
}
void buzz(int freqHZ , int howLong , int buzzFreq)
{
  for(int i =0 ; i<buzzFreq ; i++)
  {
  tone(buzzer, freqHZ); 
  delay(howLong);        
  noTone(buzzer);     
  delay(howLong);
  }
}
void buzzLed(int freqHZ , int howLong , int buzzFreq)
{
   for(int i =0 ; i<buzzFreq ; i++)
  {
    digitalWrite(pink ,1);
    delay(100);
  tone(buzzer, freqHZ); 
  delay(howLong);        
  noTone(buzzer);  
  digitalWrite(pink , 0);   
  delay(howLong);  
  } 
}

void Flight_Led(char colour , int howLong , int Freq)
{
  switch(colour)
 {
  case 'B' : for(int i = 0 ; i <= Freq ; i++)
          {
             digitalWrite(blue , HIGH);
             delay(howLong);
             digitalWrite(blue , LOW);
             delay(howLong);
          }
          break;       
   case 'P' : for(int i = 0 ; i < Freq ; i++)
          {
             digitalWrite(pink , HIGH);
             delay(howLong);
             digitalWrite(pink , LOW);
             delay(howLong);
          }
          break;
   case 'O': for(int i = 0 ; i < Freq ; i++)
          {
             digitalWrite(orange , HIGH);
             delay(howLong);
             digitalWrite(orange , LOW);
             delay(howLong);
          }
          break;
}}
