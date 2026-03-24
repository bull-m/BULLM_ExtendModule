
#ifndef BULLM_EXPAND_BULLM_EXTEND_MOS_8_H
#define BULLM_EXPAND_BULLM_EXTEND_MOS_8_H
#include "src/BULLM_I2CDevice.h"
#include "src/BULLM_PCA9685.h"

class BULLM_ExtendMos8 {
public:
    BULLM_ExtendMos8();
    BULLM_ExtendMos8(uint8_t addr);
    BULLM_ExtendMos8(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendMos8();
    bool begin();
    void setPWMFreq(float freq);

    bool setSpeed(uint8_t index, uint8_t value);
    bool setSpeedHigh(uint8_t index, uint16_t value);
    bool closeAll();
private:
    BULLM_PCA9685 *pca9685 = nullptr;
    uint8_t address;
    TwoWire *i2c = nullptr;
};


#endif //BULLM_EXPAND_BULLM_EXTEND_MOS_8_H
