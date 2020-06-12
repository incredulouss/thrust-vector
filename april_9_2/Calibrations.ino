int ledHowLong = 150;
int ledFreq = 3;
int buzHowLong = 100;

void call()
{
  buzzCal( 1000 , 1000 , 2);
  ledCal();
  buzzCal( 3000 , 200 , 1);
  servoCali(3);
  buzzCalLed( 3000 , 200 , 3);
}

void ledCal()
{
  Flight_Led('O' , ledHowLong , ledFreq );
  Flight_Led('P' , ledHowLong , ledFreq );
  Flight_Led('B' , ledHowLong , ledFreq );
}
void buzzCal(int buzzHz , int howLong , int buzzFreq)
{
  buzz(buzzHz , buzHowLong , buzzFreq);
}
void buzzCalLed(int buzzHz , int howLong , int buzzFreq )
{
buzzLed(buzzHz , howLong , buzzFreq);
}
