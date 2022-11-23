int Motorspd = 0 , MotorInitial = 100;
int kp = 1, ki = 0, kd = 0;
int error = 0, lastError = 0, integral = 0, derivative = 0;

int IRfarleft = 2, IRleft = 3,IRmid = 4, IRright = 5, IRfarright = 6;


void setup(){
  Serial.begin(9600);
  Serial.println("PID");
  pinMod(IRfarleft, INPUT);
  pinMode(IRleft, INPUT);
  pinMode(IRmid, INPUT);
  pinMode(IRright, INPUT);
  pinMode(IRfarright, INPUT);

  int sensor[5] = {IRfarleft, IRleft, IRmid, IRright, IRfarright};
}

void loop(){
  while(true){
    //print check sensor
    Serial.print("farleft: ");
    Serial.print(digitalRead(IRfarleft));
    Serial.print(" left: ");
    Serial.print(digitalRead(IRleft));
    Serial.print(" mid: ");
    Serial.print(digitalRead(IRmid));
    Serial.print(" right: ");
    Serial.print(digitalRead(IRright));
    Serial.print(" farright: ");
    Serial.println(digitalRead(IRfarright));
    delay(1000);
  }
} 

