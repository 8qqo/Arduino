#include <AFMotor.h>
#include <Servo.h>
#include <SoftwareSerial.h>

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);
Servo steeringServo;

// 定義藍牙模組的TX和RX引腳
SoftwareSerial bluetooth(10, 11); // RX, TX

int speed = 255; // 初始速度

void setup() {
  // 初始化藍牙連接
  bluetooth.begin(9600);
  Serial.begin(9600);

  // 初始化馬達控制
  motorLeft.setSpeed(speed);
  motorRight.setSpeed(speed);

  // 初始化伺服馬達控制
  steeringServo.attach(9); // 將伺服馬達連接到引腳9
  steeringServo.write(90); // 將伺服馬達初始化在中間位置
}

void loop() {
  // 讀取藍牙指令
  if (bluetooth.available() > 0) {
    char command = bluetooth.read();
    // 解析指令
    switch (command) {
      case 'W': // 前進
        motorLeft.run(FORWARD);
        motorRight.run(FORWARD);
        break;
      case 'S': // 倒退
        motorLeft.run(BACKWARD);
        motorRight.run(BACKWARD);
        break;
      case 'Q': // 加速
        speed = min(speed + 50, 255); // 最大速度255
        motorLeft.setSpeed(speed);
        motorRight.setSpeed(speed);
        break;
      case 'E': // 減速
        speed = max(speed - 50, 0); // 最小速度0
        motorLeft.setSpeed(speed);
        motorRight.setSpeed(speed);
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
        motorLeft.run(RELEASE);
        motorRight.run(RELEASE);
        break;
    }
  }
}
