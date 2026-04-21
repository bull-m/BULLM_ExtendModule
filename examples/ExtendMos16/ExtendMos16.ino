#include <Arduino.h>
#include <Wire.h>
#include "BULLM_ExtendMos16.h"

BULLM_ExtendMos16 extend(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_ExtendMos16 not found");
        return;
    }
    Serial.println("BULLM_ExtendMos16 found");

    extend.setPWMFreq(100); // 设置频率
    extend.closeAll(); // 关闭所有电机
}


void speed_all(int speed){
    for (int i = 0; i < 16; ++i) {
        extend.setSpeed(i, speed);
    }
}

void loop() {
    speed_all(127);
    delay(300);
    speed_all(255);
    delay(300);
    extend.closeAll();
    delay(200);
}


