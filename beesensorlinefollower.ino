#include <BeeLineSensorPro.h>

//M1 left moter
int enA = 10;
int in1 = 8;
int in2 = 9;

//M2

int enB = 5;
int in3 = 7;
int in4 = 6;


BeeLineSensorPro sensor = BeeLineSensorPro((unsigned char[]) {
  A0, A1, A2, A3, A4, A5, A6, A7
}, LINE_BLACK);

int SPEED = 100;

void setup() {
  Serial.begin(115200);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  for(int i=0;i<300;i++){
    sensor.calibrate();
    delay(10);
  }
}

float kP = 0.05;

void loop() {
  // mdrive(255,255);

  int err = sensor.readSensor();
  for (int i=0; i<8; i++) {
  Serial.print(sensor.values[i]);
  Serial.print('\t');

  }
  Serial.print(err);
  Serial.println(' ');

  int diff = err*kP;

  mpower(1,1,SPEED-diff);
  mpower(2,1,SPEED+diff);
}

void mpower(int motor, int rotation, int speed) {
  int pwm;
  int pA;
  int pB;
  if (motor == 1){
    pwm = enA;
    pA = in1;
    pB = in2;
  } else if ( motor == 2){
    pwm = enB;
    pA = in3;
    pB = in4;
  } else{
    return;
  }

  if (rotation == 0) {
    digitalWrite(pA, LOW);
    digitalWrite(pB,LOW);
  } else if ( rotation == 1){
    digitalWrite(pA, HIGH);
    digitalWrite(pB, LOW);
  } else if (rotation == -1){
    digitalWrite(pA, LOW);
    digitalWrite(pB, HIGH);
  }

  analogWrite(pwm, speed);

}

