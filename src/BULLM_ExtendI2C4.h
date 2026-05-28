
#ifndef BULLM_EXTEND_IIC_4_H
#define BULLM_EXTEND_IIC_4_H
#include "utils/BULLM_I2CDevice.h"
#include <Arduino.h>

class BULLM_ExtendI2C4 {
public:
    BULLM_ExtendI2C4();
    BULLM_ExtendI2C4(uint8_t addr);
    BULLM_ExtendI2C4(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendI2C4();
    bool begin();
    bool changeIIC(uint8_t index);
private:
    BULLM_I2CDevice *i2cDevice;
};


#endif //BULLM_EXTEND_IIC_4_H
