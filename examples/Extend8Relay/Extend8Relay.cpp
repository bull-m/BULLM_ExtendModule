#include <Arduino.h>
#include <Wire.h>
#include "BULLM_Extend8Relay.h"

BULLM_Extend8Relay pca(0x27);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!pca.begin()) {
        Serial.println("BULLM_Extend8Relay not found");
        return;
    }
    Serial.println("BULLM_Extend8Relay found");
    Serial.print("State before power -> ");
    Serial.println(pca.getRelayAll(), BIN); // 断电前的继电器状态

    pca.closeAllRelay(); // 关闭所有继电器

    // 设置全部的自定义引脚模式为输入
    pca.setPinModeAll(EXTEND8RELAY_PIN_MODE_INPUT);
}


void loop_relay() {
    pca.openAllRelay();
    delay(200);
    pca.closeAllRelay();
    delay(200);
    pca.openAllRelay();
    delay(200);
    pca.closeAllRelay();
    delay(300);

    for (int i = 0; i < 2; ++i) {
        pca.setRelay(0, true);
        delay(70);
        pca.setRelay(1, true);
        pca.setRelay(0, false);
        delay(70);
        pca.setRelay(2, true);
        pca.setRelay(1, false);
        delay(70);
        pca.setRelay(3, true);
        pca.setRelay(2, false);
        delay(70);
        pca.setRelay(4, true);
        pca.setRelay(3, false);
        delay(70);
        pca.setRelay(5, true);
        pca.setRelay(4, false);
        delay(70);
        pca.setRelay(6, true);
        pca.setRelay(5, false);
        delay(70);
        pca.setRelay(7, true);
        pca.setRelay(6, false);
        delay(70);
        pca.setRelay(7, false);
        delay(70);
    }
}

void loop() {
//    loop_relay(); // 继电器循环测试/

    // 将所有输入引脚状态取反设置到继电器状态 (实现：自定义引脚输入低电平时吸合继电器)
    pca.setRelayAll(~pca.getInputAll());
    delay(50);
}