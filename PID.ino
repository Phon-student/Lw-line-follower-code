
//motor pins
int enA = 3;
int in1 = 13;
int in2 = 12;

int enB = 6;
int in3 = 11;
int in4 = 5;

//PID variables
int Motorspd = 0 , MotorInitial = 180;
int kp = 1, ki = 0, kd = 0;
int lastError = 0, derivative = 0;

int limit = 255;
int lowlimit = 0;

int counts = 0;

//IR sensor pins
int IRfarleft = A1;
int IRleft = A2;
int IRmid = A3;
int IRright = A4;
int IRfarright = A5;

// pin calibrations
int PWML = enA;
int PWMR = enB;

int IRfarleftval = 0;
int IRleftval = 0;
int IRmidval = 0;
int IRrightval = 0;
int IRfarrightval = 0;


//functions





//setup
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(IRfarleft, INPUT);
  pinMode(IRleft, INPUT);
  pinMode(IRmid, INPUT);
  pinMode(IRright, INPUT);
  pinMode(IRfarright, INPUT);
}
 


//main loop

void loop(){
  valueRead();
  PID();
  IRprint();
  Serial.println("PWML:");
  Serial.println(PWML);
  Serial.println("PWMR:");
  Serial.print(PWMR);



} 

//functions

void valueRead(){
  IRfarleftval = analogRead(IRfarleft);
  IRleftval = analogRead(IRleft);
  IRmidval = analogRead(IRmid);
  IRrightval = analogRead(IRright);
  IRfarrightval = analogRead(IRfarright);
}


//PID function to control motors based on IR sensor values
void PID(){
  int error = IRmidval - 500;
  derivative = error - lastError;
  Motorspd = (kp * error) + (ki * counts) + (kd * derivative);
  lastError = error;
  counts = counts + error;
  PWML = MotorInitial + Motorspd;
  PWMR = MotorInitial - Motorspd;
  if (PWML > limit){
    PWML = limit;
  }
  if (PWMR > limit){
    PWMR = limit;
  }
  if (PWML < lowlimit){
    PWML = lowlimit;
  }
  if (PWMR < lowlimit){
    PWMR = lowlimit;
  }
  if (error > 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, PWML);
    analogWrite(enB, PWMR);
  }
  if (error < 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enA, PWML);
    analogWrite(enB, PWMR);
  }
  if (error == 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, MotorInitial);
    analogWrite(enB, MotorInitial);
  }
  
}





//IR sensor print
void IRprint(){
  Serial.print("IRfarleftval: ");
  Serial.print(IRfarleftval);
  Serial.print("IRleftval: ");
  Serial.print(IRleftval);
  Serial.print("IRmidval: ");
  Serial.print(IRmidval);
  Serial.print("IRrightval: ");
  Serial.print(IRrightval);
  Serial.print("IRfarrightval: ");
  Serial.print(IRfarrightval);
}

