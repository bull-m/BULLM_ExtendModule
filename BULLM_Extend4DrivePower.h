
#ifndef BULLM_EXPAND_BULLM_EXTEND4DRIVE_POWER_H
#define BULLM_EXPAND_BULLM_EXTEND4DRIVE_POWER_H
#include "src/BULLM_I2CDevice.h"
#include "src/BULLM_PCA9685.h"

class BULLM_Extend4DrivePower {
public:
    BULLM_Extend4DrivePower();
    BULLM_Extend4DrivePower(uint8_t addr);
    BULLM_Extend4DrivePower(uint8_t addr, TwoWire &i2c);
    ~BULLM_Extend4DrivePower();
    bool begin();

    bool setSpeed(uint8_t index, int value, bool isBrake = false);
    bool setSpeedHigh(uint8_t index, int value, bool isBrake = false);
    bool brake(uint8_t index);
    bool closeAll();
private:
    BULLM_PCA9685 *pca9685 = nullptr;
    uint8_t address;
    TwoWire *i2c = nullptr;
};


#endif //BULLM_EXPAND_BULLM_EXTEND4DRIVE_POWER_H
