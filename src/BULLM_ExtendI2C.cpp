#include "BULLM_ExtendI2C.h"

BULLM_ExtendI2C::BULLM_ExtendI2C() {
    i2cDevice = new BULLM_I2CDevice(0x77, Wire);
}

BULLM_ExtendI2C::BULLM_ExtendI2C(uint8_t addr) {
    i2cDevice = new BULLM_I2CDevice(addr, Wire);
}

BULLM_ExtendI2C::BULLM_ExtendI2C(uint8_t addr, TwoWire &i2c) {
    i2cDevice = new BULLM_I2CDevice(addr, i2c);
}

BULLM_ExtendI2C::~BULLM_ExtendI2C() {
    if (i2cDevice) delete i2cDevice;
    i2cDevice = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendI2C::begin() {
    return i2cDevice->begin();
}

bool BULLM_ExtendI2C::selectChannel(uint8_t channel) {
    if (channel > 7) return false;
    uint8_t reg = 1 << channel;
    return i2cDevice->write(&reg, 1);
}

bool BULLM_ExtendI2C::enableChannel(uint8_t channel) {
    if (channel > 7) return false;
    uint8_t state = readState();
    state |= (1 << channel);
    return i2cDevice->write(&state, 1);
}

bool BULLM_ExtendI2C::disableChannel(uint8_t channel) {
    if (channel > 7) return false;
    uint8_t state = readState();
    state &= ~(1 << channel);
    return i2cDevice->write(&state, 1);
}

bool BULLM_ExtendI2C::closeAll() {
    uint8_t reg = 0;
    return i2cDevice->write(&reg, 1);
}

uint8_t BULLM_ExtendI2C::readState() {
    uint8_t state = 0;
    i2cDevice->read(&state, 1);
    return state;
}
