#include <Arduino.h>
#include <Wire.h>
#include <BULLM_ExtendMotor8.h>

BULLM_ExtendMotor8 extend(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);
    // 初始化扩展版
    if (!extend.begin()) {
        Serial.println("BULLM_ExtendMotor8 not found");
        return;
    }
    Serial.println("BULLM_ExtendMotor8 found");
    extend.closeAll();  // 关闭所有电机
    extend.setPwmFreq(1000); // 将PWM频率设置为1000Hz
}

// 设置所有电机速度
void speed_all(int speed){
    for (int i = 0; i < 8; ++i) {
        extend.setSpeed(i, speed);
    }
}

void loop() {
    speed_all(127);
    delay(500);
    speed_all(255);
    delay(500);
    extend.closeAll();
    delay(500);
    speed_all(-127);
    delay(500);
    speed_all(-255);
    delay(500);
    extend.closeAll();
    delay(500);
}