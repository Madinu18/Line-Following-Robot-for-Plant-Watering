#define CW  0
#define CC 1
#define MOTOR_A 0
#define MOTOR_B 1

#define S0 7
#define S1 8
#define S2 4
#define S3 3
#define sensorOut 5

#define Pump 9

const int E1 = 10;
const int E2 = 11;
const int M1 = 12;
const int M2 = 13;

const int SENSOR1 = 6;
const int SENSOR2 = 2;

int A, B;
int SPD = 190;
int length = 10;

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

void setup() {
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(SENSOR1, INPUT);
  pinMode(SENSOR2, INPUT);
 
  digitalWrite(E1, LOW);
  digitalWrite(E2, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(Pump, OUTPUT);

  Serial.begin(9600);
}

void drive(byte motor, byte dir,byte spd){
  if (motor == MOTOR_A)
  {
  digitalWrite(M1, dir);
  analogWrite(E1, spd);
  }
  else if (motor == MOTOR_B)
  {
  digitalWrite(M2, dir);
  analogWrite(E2, spd);
  } 
}

void stop(byte motor){
  drive(motor, 0, 0);
}

void loop() {
  
  A = digitalRead(SENSOR1);
  B = digitalRead(SENSOR2);
 
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, 15, 149, 255,0);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  greenColor = map(greenFrequency, 27, 117, 255, 0);
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  blueColor = map(blueFrequency, 9, 73, 255, 0);

 if(blueColor > redColor && blueColor > greenColor && redColor < 0){
    stop(MOTOR_A);
    stop(MOTOR_B);
  }
  else if(greenColor > redColor && greenColor > blueColor && greenColor < 0){
    Serial.print(redColor);
    stop(MOTOR_A);
    stop(MOTOR_B);
    delay(500);
    digitalWrite(Pump, HIGH);
    delay(750);
    digitalWrite(Pump, LOW);
    stop(MOTOR_A);
    stop(MOTOR_B);
    delay(500);
    drive(MOTOR_A,CW,SPD);
    drive(MOTOR_B,CW,SPD);
    delay(250);
   }
  else {
    if (A == 1) {                       
      drive(MOTOR_B,CC,SPD); 
    }
    else if (A == 0) {              
      drive(MOTOR_B,CW,SPD);  
    }
    if (B == 1) {                      
      drive(MOTOR_A,CC,SPD); 
    }
    else if (B == 0) {                 
      drive(MOTOR_A,CW,SPD);  
    }
  }
}
