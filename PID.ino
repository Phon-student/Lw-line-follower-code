#define ENA 3//right motor
#define motorInput1 13
#define motorInput2 12

#define motorInput3 11
#define motorInput4 5
#define ENB 6//left motor

#define sensorsamount 5 //amount of sensors

float P=0;
float I=0;
float D=0;
float error = 0, LPerror = 0;

int rightmotor_spd, leftmotor_spd, maxspeed = 255;//max speed of motors

long Sensor_avarage;
int Sensor_sum;
int position;
long sensor[]={0,0,0,0,0};
int i;
int p[]={0,0,0,0,0};


//functions list declaration

void read_sensors();
void PID();
void turning();
void driver(int, int);
int motor_set(int, int);
void forward();
void backward();
void left();
void right();
void stop();
void line_read();
int mod(int);

void setup(){
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorInput3, OUTPUT);
  pinMode(motorInput4, OUTPUT);
}



void loop(){
  forward();
  delay(1000);
  if(delay > 1000){
    read_sensors();
    PID();
    turning();
    driver(rightmotor_spd, leftmotor_spd);
  }
}

void read_sensors(){
  Sensor_avarage = 0;
  Sensor_sum = 0;
  for(i=0;i<sensorsamount;i++){
    sensor[i] = analogRead(i);
    Sensor_avarage += sensor[i]*i;
    Sensor_sum += sensor[i];
  }
  position = Sensor_avarage/Sensor_sum;
}

void PID(){
  position = int(Sensor_avarage/Sensor_sum);
  P=position-2;
  I=I+P;
  D=P-LPerror;
  LPerror=P;
  error= int(P*kp+I*ki+D*kd);
}

void turning(){
  error = int(constrain(error,-maxspeed,maxspeed));
  Serial.println(error);

  if(error < 0){
    rightmotor_spd = maxspeed + error;
    leftmotor_spd = maxspeed;
  }
  else{
    rightmotor_spd = maxspeed;
    leftmotor_spd = maxspeed - error;
  }
}

void driver(int rightmotor_spd, int leftmotor_spd){
  analogWrite(ENB, rightmotor_spd);
  analogWrite(ENA, leftmotor_spd);
  forward();
}

void line_read(){
  p[0]=analogRead(A1);
  p[1]=analogRead(A2);
  p[2]=analogRead(A3);
  p[3]=analogRead(A4);
  p[4]=analogRead(A5);
  for(i=0;i<5;i++){
    if(p[i]>700){    //check the value read against the threshold
      p[i]=1;
    }
    else{
      p[i]=0;
    }
  }
}


//drive functions
void forward(){
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}

void backward(){
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}

void left(){
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}

void right(){
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}

void left_turn90(){
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, HIGH);
}

void right_turn90(){
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  
  digitalWrite(motorInput3, HIGH);
  digitalWrite(motorInput4, LOW);
}

void stop(){
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
  
  digitalWrite(motorInput3, LOW);
  digitalWrite(motorInput4, LOW);
}


//PID functions
int mod(int v){
  if(v<0){
    return -1 * -v;
  }
  else if(v>0){
    return v;
  }
}