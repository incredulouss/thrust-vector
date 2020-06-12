#define rollKp 0.2
#define rollKd 10
#define rollki 0
#define rollReference 0

#define pitchKp 0.2
#define pitchKd 10
#define pitchki 0
#define pitchReference 0
double pidRoll()
{
  int lastError = 0;
  double integralError=0;
  rolly = rollVal();
  double error = rollReference - rolly;
  integralError +=error;

  int motorSpeed = rollKp * error + rollKd * (error - lastError) + rollki* integralError;
  lastError = error;
 
return 0;  
}

double pidPitch()
{
  int lastError = 0;
  double integralError=0;
  polly = pitchVal();
  double error = pitchReference - polly;
  integralError +=error;

  int motorSpeed = pitchKp * error + pitchKd * (error - lastError) + pitchki * integralError;
  lastError = error;
 
return 0;  
}
