#define motorPin1  3
#define motorPin2  6
#define IRfarleft  A1 
#define IRleft  A2
#define IRmid  A3
#define IRright  A4
#define IRfarright  A5

int Motorspd = 0 , MotorInitial = 100;
int kp = 1, ki = 0, kd = 0;
int lastError = 0, derivative = 0;


void setup(){
  Serial.begin(19200);
  Serial.println("PID");
  pinMode(IRfarleft, INPUT);
  pinMode(IRleft, INPUT);
  pinMode(IRmid, INPUT);
  pinMode(IRright, INPUT);
  pinMode(IRfarright, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop(){
  read();
  PID();
  Serial.println(Motorspd);

} 


void read(){
    Serial.println(analogRead(IRfarleft));
    Serial.println(analogRead(IRleft));
    Serial.println(analogRead(IRmid));
    Serial.println(analogRead(IRright));
    Serial.println(analogRead(IRfarright));
  
    delay(1000);
}

void PID(){
  int error = analogRead(IRmid) - 500;
  derivative = error - lastError;
  Motorspd = MotorInitial + (kp * error) + (ki * error) + (kd * derivative);
  lastError = error;
  if(Motorspd > 255){
    Motorspd = 255;
  }
  if(Motorspd < 0){
    Motorspd = 0;
  }
  analogWrite(motorPin1, Motorspd);
  analogWrite(motorPin2, Motorspd);
}

