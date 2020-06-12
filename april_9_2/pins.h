//IMU
Kalman kalmanX;
Kalman kalmanY;
Kalman kalmanZ;
#define RESTRICT_PITCH 0

int ledB = 4;
/* IMU Data */
double imuRollReference = 0;
double imuPitchReference = 0;
double calRolly , calPolly;
double errorRoll , errorPoll;
double rolly,polly,yolly;
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
int16_t tempRaw;

double gyroXangle, gyroYangle, gyroZangle; 
double compAngleX, compAngleY, compAngleZ; 
double kalAngleX, kalAngleY, kalAngleZ; 

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

double roll,pitch,yaw,temperature;
double gyroXrate,gyroYrate,gyroZrate;
double dt;

//SERVO
#define correctionFactorX 0
#define correctionFactorY 0
Servo myservoX;
Servo myservoY; 
int maxAngleX = 110 , maxAngleY = 110;
int minAngleX = 25 , minAngleY = 25;
int refAngleX = 70;
int refAngleY = 70;

//LED &&  BUZZER
int pink = A2;
int orange = A1;
int blue =  2;

#define buzzer 9

char state = 'a';

//PYRO channels
#define noOfPyro 4
#define pyro1 A7
#define pyro2 A0
#define pyro3 9
#define pyro4 10
int duration = 3000;
