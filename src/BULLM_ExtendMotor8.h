
#ifndef BULLM_EXTEND_MOTOR_8_H
#define BULLM_EXTEND_MOTOR_8_H
#include "utils/BULLM_I2CDevice.h"
#include "utils/BULLM_PCA9685.h"

class BULLM_ExtendMotor8 {
public:
    BULLM_ExtendMotor8();
    BULLM_ExtendMotor8(uint8_t addr);
    BULLM_ExtendMotor8(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendMotor8();
    bool begin();
    bool setPwmFreq(uint16_t freq);
    bool setSpeed(uint8_t index, int value);
    bool setSpeedRaw(uint8_t index, int value);
    bool closeAll();
private:
    BULLM_PCA9685 *pca9685;
};


#endif //BULLM_EXTEND_MOTOR_8_H
