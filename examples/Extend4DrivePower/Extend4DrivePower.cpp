#include <Arduino.h>
#include <Wire.h>
#include "BULLM_Extend4DrivePower.h"

BULLM_Extend4DrivePower pca(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!pca.begin()) {
        Serial.println("BULLM_Extend4DrivePower not found");
        return;
    }
    Serial.println("BULLM_Extend4DrivePower found");
    pca.closeAll(); // 关闭所有电机
}


void loop() {
    pca.setSpeed(0, 255);
    delay(1500);
    pca.setSpeed(0, 0, true); // 刹车停止
    delay(1500);
}