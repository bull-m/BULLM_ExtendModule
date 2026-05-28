#include <Arduino.h>
#include <Wire.h>
#include "BULLM_ExtendI2C4.h"

BULLM_ExtendI2C4 extend(0x77);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_ExtendI2C4 not found");
        return;
    }
    Serial.println("BULLM_ExtendI2C4 found");
    extend.changeIIC(0); // 切换到通道1
}

void loop() {
    delay(300);
}