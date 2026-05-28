#include <Arduino.h>
#include <Wire.h>
#include "BULLM_ExtendPwm.h"

BULLM_ExtendPwm extend(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_ExtendPwm not found");
        return;
    }
    Serial.println("BULLM_ExtendPwm found");
    extend.closeAllPwm(); // 关闭所有PWM输出
    extend.setPwmFreq(100); // 设置频率
}

// 设置所有的Pwm
void speed_all(int speed){
    for (int i = 0; i < 16; ++i) {
        extend.setPwm(i, speed);
    }
}

void loop() {
    speed_all(100);
    delay(500);
    extend.closeAllPwm();
    delay(500);
    speed_all(255);
    delay(500);
    extend.closeAllPwm();
    delay(500);
}