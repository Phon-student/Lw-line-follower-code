int Motorspd = 0 , MotorInitial = 100;
int kp = 1, ki = 0, kd = 0;
int lastError = 0, derivative = 0;


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
  PID();
  Serial.println(Motorspd);
} 
int error(){
  sensor[0] << IRfarleft; 
  sensor[1] << IRleft;
  sensor[2] << IRmid;
  sensor[3] << IRright;
  sensor[4] << IRfarright;

  if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==1))
  error=4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==1))
  error=3;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==1)&&(sensor[4]==0))
  error=2;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==1)&&(sensor[4]==0))
  error=1;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0))
  error=0;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==1)&&(sensor[3]==0)&&(sensor[4]==0))
  error=-1;
  else if((sensor[0]==0)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0))
  error=-2;
  else if((sensor[0]==1)&&(sensor[1]==1)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0))
  error=-3;
  else if((sensor[0]==1)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0))
  error=-4;
  else if((sensor[0]==0)&&(sensor[1]==0)&&(sensor[2]==0)&&(sensor[3]==0)&&(sensor[4]==0))
    if(error==-4) error=-5;
    else error=5;
  return error;
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

void PID(int error){
  derivative = error - lastError;
  Motorspd = MotorInitial + (kp*error) + (kd*derivative);
  lastError = error;
  Motorspd = MotorInitial;
}