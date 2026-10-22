#ifndef BULLM_EXTEND_IIC_H
#define BULLM_EXTEND_IIC_H
#include "utils/BULLM_I2CDevice.h"
#include <Arduino.h>

class BULLM_ExtendI2C {
public:
    BULLM_ExtendI2C();
    BULLM_ExtendI2C(uint8_t addr);
    BULLM_ExtendI2C(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendI2C();
    bool begin();
    bool selectChannel(uint8_t channel);
    bool enableChannel(uint8_t channel);
    bool disableChannel(uint8_t channel);
    bool closeAll();
    uint8_t readState();
private:
    BULLM_I2CDevice *i2cDevice;
};

#endif //BULLM_EXTEND_IIC_H
