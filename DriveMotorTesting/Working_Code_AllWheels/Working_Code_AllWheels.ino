//MOTOR1 PINS
int ena = 5;
int in1 = 6;
int in2 = 7;

//MOTOR2 PINS
int enb = 10;
int in3 = 8;
int in4 = 9;

void setup() {
  

};

void loop() {

  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //CLOCKWISE MAX SPEED
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
  delay(2000);

  //STOP
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);

  //COUNTERCLOCKWISE MAX SPEED
  digitalWrite(in1, LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4,HIGH);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
  delay(2000);

  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(2000);

  //CLOCKWISE HALF SPEED
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  analogWrite(ena, 127);
  analogWrite(enb, 127);
  delay(2000);

  //STOP
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  delay(2000);

  //COUNTERCLOCKWISE MAX SPEED
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  analogWrite(ena, 127);
  analogWrite(enb, 127);
  delay(2000);

  


}
