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
    extend.openAllRelay();
    delay(200);
    extend.closeAllRelay();
    delay(200);
    extend.openAllRelay();
    delay(200);
    extend.closeAllRelay();
    delay(300);

    for (int i = 0; i < 2; ++i) {
        extend.setRelay(0, true);
        delay(70);
        extend.setRelay(1, true);
        extend.setRelay(0, false);
        delay(70);
        extend.setRelay(2, true);
        extend.setRelay(1, false);
        delay(70);
        extend.setRelay(3, true);
        extend.setRelay(2, false);
        delay(70);
        extend.setRelay(4, true);
        extend.setRelay(3, false);
        delay(70);
        extend.setRelay(5, true);
        extend.setRelay(4, false);
        delay(70);
        extend.setRelay(6, true);
        extend.setRelay(5, false);
        delay(70);
        extend.setRelay(7, true);
        extend.setRelay(6, false);
        delay(70);
        extend.setRelay(7, false);
        delay(70);
    }
}

void loop() {
//    loop_relay(); // 继电器循环测试/

    // 将所有输入引脚状态取反设置到继电器状态 (实现：自定义引脚输入低电平时吸合继电器)
    extend.setRelayAll(~extend.getInputAll());
    delay(50);
}