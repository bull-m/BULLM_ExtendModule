
#ifndef BULLM_EXTEND4DRIVE_POWER_H
#define BULLM_EXTEND4DRIVE_POWER_H
#include "utils/BULLM_I2CDevice.h"
#include "utils/BULLM_PCA9685.h"

class BULLM_Extend4DrivePower {
public:
    BULLM_Extend4DrivePower();
    BULLM_Extend4DrivePower(uint8_t addr);
    BULLM_Extend4DrivePower(uint8_t addr, TwoWire &i2c);
    ~BULLM_Extend4DrivePower();
    bool begin();
    void setPWMFreq(float freq);

    bool setSpeed(uint8_t index, int value, bool isBrake = false);
    bool setSpeedHigh(uint8_t index, int value, bool isBrake = false);
    bool brake(uint8_t index);
    bool closeAll(bool isBrake = false);
private:
    BULLM_PCA9685 *pca9685 = nullptr;
    uint8_t address;
    TwoWire *i2c = nullptr;
};


#endif //BULLM_EXTEND4DRIVE_POWER_H
