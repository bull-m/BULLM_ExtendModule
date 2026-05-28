#ifndef BULLM_PCA9536_H
#define BULLM_PCA9536_H
#include <Arduino.h>
#include "BULLM_I2CDevice.h"
// 寄存器地址
#define PCA9536_INPUT      0x00
#define PCA9536_OUTPUT     0x01
#define PCA9536_POLARITY   0x02
#define PCA9536_CONFIG     0x03

#define PCA9536_MODE_OUTPUT  0
#define PCA9536_MODE_INPUT   1

class BULLM_PCA9536 {
public:
    BULLM_PCA9536();
    BULLM_PCA9536(uint8_t addr);
    BULLM_PCA9536(uint8_t addr, TwoWire &i2c);
    ~BULLM_PCA9536();
    bool begin();
    uint8_t readRegister(uint8_t reg);
    bool writeRegister(uint8_t reg, uint8_t data);
    uint8_t readPort();
    uint8_t readPin(uint8_t pin);
    bool writePort(uint8_t data);
    bool writePin(uint8_t pin, bool state);
    bool setConfig(uint8_t modes);
    bool setConfigPin(uint8_t pin, uint8_t mode);
    bool setPolarity(uint8_t reverses);
    bool setPolarityPin(uint8_t pin, uint8_t reverse);
private:
    BULLM_I2CDevice *i2cDevice;
};


#endif //BULLM_PCA9536_H
