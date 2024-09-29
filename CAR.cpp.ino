#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);
Servo steeringServo;

const int enA = 3; // PWM 速度控制輸出
const int in1 = 4; // 馬達1方向控制
const int in2 = 5; // 馬達1方向控制
const int in3 = 6; // 馬達2方向控制
const int in4 = 7; // 馬達2方向控制

int speed = 255; // 初始速度

void setup() {
  Serial.begin(9600);

  // 初始化馬達控制
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(speed);

  // 初始化伺服馬達控制
  steeringServo.attach(9); // 將伺服馬達連接到引腳9
  steeringServo.write(90); // 將伺服馬達初始化在中間位置
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    // 解析指令
    switch (command) {
      case 'W': // 前進
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(enA, speed);
        break;
      case 'S': // 倒退
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(enA, speed);
        break;
      case 'Q': // 加速
        speed = min(speed + 50, 255); // 最大速度255
        analogWrite(enA, speed);
        break;
      case 'E': // 減速
        speed = max(speed - 50, 0); // 最小速度0
        analogWrite(enA, speed);
        break;
      case 'A': // 左轉
        // 控制伺服馬達向左轉
        steeringServo.write(0);
        break;
      case 'D': // 右轉
        // 控制伺服馬達向右轉
        steeringServo.write(180);
        break;
      case 'R': // 停止
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        break;
    }
  }
}
