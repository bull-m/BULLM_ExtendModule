
#ifndef BULLM_EXTEND_MOTOR_4_H
#define BULLM_EXTEND_MOTOR_4_H
#include "utils/BULLM_I2CDevice.h"
#include "utils/BULLM_PCA9685.h"

class BULLM_ExtendMotor4 {
public:
    BULLM_ExtendMotor4();
    BULLM_ExtendMotor4(uint8_t addr);
    BULLM_ExtendMotor4(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendMotor4();
    bool begin();
    void setPwmFreq(float freq);
    bool setSpeed(uint8_t index, int value, bool isBrake = false);
    bool setSpeedHigh(uint8_t index, int value, bool isBrake = false);
    bool brake(uint8_t index);
    bool closeAll(bool isBrake = false);
private:
    BULLM_PCA9685 *pca9685;
};


#endif //BULLM_EXTEND_MOTOR_4_H
