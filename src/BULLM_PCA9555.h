#ifndef BULLM_EXPAND_BULLM_PCA9555_H
#define BULLM_EXPAND_BULLM_PCA9555_H
#include <Arduino.h>
#include "BULLM_I2CDevice.h"
// 寄存器地址
#define PCA9555_INPUT0      0x00
#define PCA9555_INPUT1      0x01
#define PCA9555_OUTPUT0     0x02
#define PCA9555_OUTPUT1     0x03
#define PCA9555_POLARITY0   0x04
#define PCA9555_POLARITY1   0x05
#define PCA9555_CONFIG0     0x06
#define PCA9555_CONFIG1     0x07

#define PCA9555_MODE_OUTPUT  0
#define PCA9555_MODE_INPUT   1

class BULLM_PCA9555 {
public:
    BULLM_PCA9555();
    BULLM_PCA9555(uint8_t addr);
    BULLM_PCA9555(uint8_t addr, TwoWire &i2c);
    ~BULLM_PCA9555();
    bool begin();
    uint8_t readRegister(uint8_t reg);
    bool writeRegister(uint8_t reg, uint8_t data);
    uint8_t readPort(uint8_t port);
    uint8_t readPin(uint8_t port, uint8_t pin);
    bool writePort(uint8_t port, uint8_t data);
    bool writePin(uint8_t port, uint8_t pin, bool state);
    bool setConfig(uint8_t port, uint8_t modes);
    bool setConfigPin(uint8_t port, uint8_t pin, uint8_t mode);
    bool setPolarity(uint8_t port, uint8_t reverses);
    bool setPolarityPin(uint8_t port, uint8_t pin, uint8_t reverse);
private:
    BULLM_I2CDevice *i2cDevice = nullptr;
    uint8_t i2caddr = 0;
    TwoWire *i2c = nullptr;
};


#endif //BULLM_EXPAND_BULLM_PCA9555_H
