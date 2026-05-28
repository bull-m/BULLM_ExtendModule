#include <Arduino.h>
#include <Wire.h>
#include "BULLM_Extend8Relay.h"

BULLM_Extend8Relay extend(0x27);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_Extend8Relay not found");
        return;
    }
    Serial.println("BULLM_Extend8Relay found");
    Serial.print("State before power -> ");
    Serial.println(extend.getRelayAll(), BIN); // 断电前的继电器状态

    extend.closeAllRelay(); // 关闭所有继电器

    // 设置全部的自定义引脚模式为输入
    extend.setPinModeAll(EXTEND8RELAY_PIN_MODE_INPUT);
}


void loop_relay() {
    for (int i = 0; i < 2; ++i) {
        extend.openAllRelay();
        delay(300);
        extend.closeAllRelay();
        delay(300);
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (j < 8) extend.setRelay(j, true);
            if (j > 0) extend.setRelay(j - 1, false);
            delay(100);
        }
    }

    delay(150);
}

void loop() {
//    loop_relay(); // 继电器循环测试/

    // 将所有输入引脚状态取反设置到继电器状态 (实现：自定义引脚输入低电平时吸合继电器)
    extend.setRelayAll(~extend.getInputAll());
    delay(50);
}