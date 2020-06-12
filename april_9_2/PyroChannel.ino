
void pyroInit()
{
  pinMode(pyro1,OUTPUT);
  pinMode(pyro2,OUTPUT);
  pinMode(pyro3,OUTPUT);
  pinMode(pyro4,OUTPUT);
}

void firePyro(int no)
{
  switch(no)
  {
    case 1: digitalWrite(pyro1,HIGH);
            delay(duration);
            digitalWrite(pyro1,LOW);
            delay(100);
            break;

    case 2: digitalWrite(pyro2,HIGH);
            delay(duration);
            digitalWrite(pyro2,LOW);
            delay(100);
            break;

    case 3: digitalWrite(pyro3,HIGH);
            delay(duration);
            digitalWrite(pyro3,LOW);
            delay(100);
            break;

    case 4: digitalWrite(pyro1,HIGH);
            delay(duration);
            digitalWrite(pyro2,LOW);
            delay(100);
            break;
  }
}
void pyrofire()
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
      case 'B': firePyro(1);
                break;
                
      case 'C': firePyro(2);
                break;
                
      case 'D': firePyro(3);
                break;
                
      case 'E': firePyro(4);
                break;
                
       case 'G': check = 'f';
                 break;
      }
    }
}
}
