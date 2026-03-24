#include <Arduino.h>
#include <Wire.h>
#include "BULLM_Extend4DrivePower.h"

BULLM_Extend4DrivePower extend(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_Extend4DrivePower not found");
        return;
    }
    Serial.println("BULLM_Extend4DrivePower found");

    extend.setPWMFreq(100); // 设置频率
    extend.closeAll(); // 关闭所有电机
}


void loop() {
    extend.setSpeed(0, 100);
    extend.setSpeed(1, 100);
    extend.setSpeed(2, 100);
    extend.setSpeed(3, 100);
    delay(2000);
    extend.closeAll(); // 全部停止
    delay(2000);
}