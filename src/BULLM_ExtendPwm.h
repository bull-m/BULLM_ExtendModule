
#ifndef BULLM_EXTEND_PWM_H
#define BULLM_EXTEND_PWM_H
#include "utils/BULLM_I2CDevice.h"
#include "utils/BULLM_PCA9685.h"

class BULLM_ExtendPwm {
public:
    BULLM_ExtendPwm();
    BULLM_ExtendPwm(uint8_t addr);
    BULLM_ExtendPwm(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendPwm();

    bool begin();

    bool setPwmFreq(uint16_t freq);
    bool setPwm(uint8_t index, uint8_t value);
    bool setPwmRaw(uint8_t index, uint16_t value);
    bool closeAllPwm();
private:
    BULLM_PCA9685 *pca9685;
};


#endif //BULLM_EXTEND_PWM_H
