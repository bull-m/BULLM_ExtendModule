#include <Arduino.h>
#include <Wire.h>
#include "BULLM_ExtendMotor4.h"

BULLM_ExtendMotor4 extend(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_ExtendMotor4 not found");
        return;
    }
    Serial.println("BULLM_ExtendMotor4 found");
    extend.closeAll();  // 关闭所有电机
    extend.setPwmFreq(100); // 设置频率
}


void loop() {
    extend.setSpeed(0, 100); // 电机0转速100
    extend.setSpeed(1, 100);
    extend.setSpeed(2, 100);
    extend.setSpeed(3, 100);
    delay(2000);
    extend.closeAll(); // 全部停止
    delay(2000);
}