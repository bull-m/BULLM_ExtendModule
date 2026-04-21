
#ifndef BULLM_EXTEND_MOS_16_H
#define BULLM_EXTEND_MOS_16_H
#include "utils/BULLM_I2CDevice.h"
#include "utils/BULLM_PCA9685.h"

class BULLM_ExtendMos16 {
public:
    BULLM_ExtendMos16();
    BULLM_ExtendMos16(uint8_t addr);
    BULLM_ExtendMos16(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendMos16();
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


#endif //BULLM_EXTEND_MOS_16_H
