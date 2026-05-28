// 新版继电器控制示例

#include <Arduino.h>
#include <Wire.h>
#include "BULLM_ExtendRelay.h"

BULLM_ExtendRelay extend(0x41);

void setup() {
    Wire.begin(); // 初始化I2C
    Serial.begin(9600);

    if (!extend.begin()) {
        Serial.println("BULLM_ExtendRelay not found");
        return;
    }
    Serial.println("BULLM_ExtendRelay found");
    Serial.print("State before power -> ");
    Serial.println(extend.getRelayAll(), BIN); // 断电前的继电器状态

    extend.closeAllRelay(); // 关闭所有继电器
}


void loop() {
    for (int i = 0; i < 2; ++i) {
        extend.openAllRelay();
        delay(300);
        extend.closeAllRelay();
        delay(300);
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (j < 4) extend.setRelay(j, true);
            if (j > 0) extend.setRelay(j - 1, false);
            delay(100);
        }
    }

    delay(150);
}
