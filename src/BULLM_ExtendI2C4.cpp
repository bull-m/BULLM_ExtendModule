#include "BULLM_ExtendI2C4.h"

BULLM_ExtendI2C4::BULLM_ExtendI2C4() {
    i2cDevice = new BULLM_I2CDevice(0x77, Wire);
}

BULLM_ExtendI2C4::BULLM_ExtendI2C4(const uint8_t addr) {
    i2cDevice = new BULLM_I2CDevice(addr, Wire);
}

BULLM_ExtendI2C4::BULLM_ExtendI2C4(const uint8_t addr, TwoWire &i2c) {
    i2cDevice = new BULLM_I2CDevice(addr, i2c);
}

BULLM_ExtendI2C4::~BULLM_ExtendI2C4() {
    if (i2cDevice) delete i2cDevice;
    i2cDevice = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendI2C4::begin() {
    return i2cDevice->begin();
}


bool BULLM_ExtendI2C4::changeIIC(uint8_t index) {
    if (index > 3) return false;
    uint8_t reg = 0;
    reg |= (1 << index);
    uint8_t buffer[2] = {reg};
    return i2cDevice->write(buffer, 1);
}

