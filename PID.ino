int Motorspd = 0 , MotorInitial = 100;
int kp = 1, ki = 0, kd = 0;
int error = 0, lastError = 0, integral = 0, derivative = 0;

int IRfarleft = 0, IRleft = 2,IRmid = 4, IRright = 6, IRfarright = 8;


void setup(){
  Serial.begin(9600);
  Serial.println("PID");
  pinMode(IRfarleft, INPUT);
  pinMode(IRleft, INPUT);
  pinMode(IRmid, INPUT);
  pinMode(IRright, INPUT);
  pinMode(IRfarright, INPUT);
}

void loop(){
  read();
  
} 

void read(){
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

