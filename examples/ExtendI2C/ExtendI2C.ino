#include <Arduino.h>
#include <Wire.h>
#include "BULLM_ExtendI2C.h"

// 该库同时支持4通道扩展模块和8通道扩展模块，请注意切换通道时的范围
BULLM_ExtendI2C extend(0x77);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_ExtendI2C not found");
        return;
    }
    Serial.println("BULLM_ExtendI2C found");

    extend.selectChannel(0); // 切换到通道0
}

void loop() {
    delay(300);
}