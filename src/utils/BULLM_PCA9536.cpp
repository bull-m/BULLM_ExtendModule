#include "BULLM_PCA9536.h"

namespace {
    constexpr uint8_t PCA9536_DEFAULT_ADDRESS = 0x41;
    constexpr uint8_t PCA9536_PIN_MASK = 0x0F;
    constexpr uint8_t PCA9536_MAX_PIN = 3;
}

BULLM_PCA9536::BULLM_PCA9536() {
    i2cDevice = new BULLM_I2CDevice(PCA9536_DEFAULT_ADDRESS, Wire);
}

BULLM_PCA9536::BULLM_PCA9536(const uint8_t addr) {
    i2cDevice = new BULLM_I2CDevice(addr, Wire);
}

BULLM_PCA9536::BULLM_PCA9536(const uint8_t addr, TwoWire &i2c) {
    i2cDevice = new BULLM_I2CDevice(addr, i2c);
}

BULLM_PCA9536::~BULLM_PCA9536() {
    delete i2cDevice;
    i2cDevice = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_PCA9536::begin() {
    return i2cDevice->begin();
}

// 在PCA9536读单个寄存器
uint8_t BULLM_PCA9536::readRegister(uint8_t reg) {
    if (!i2cDevice) {
        return 0;
    }
    uint8_t buffer[1] = {reg};
    bool res = i2cDevice->write_then_read(buffer, 1, buffer, 1);
    if (!res) {
        return 0;
    }
    return buffer[0];
}

// 向PCA9536写单个寄存器
bool BULLM_PCA9536::writeRegister(uint8_t reg, uint8_t data) {
    if (!i2cDevice) {
        return false;
    }
    uint8_t buffer[2] = {reg, data};
    return i2cDevice->write(buffer, 2);
}

// 读取4位输入端口
uint8_t BULLM_PCA9536::readPort() {
    return readRegister(PCA9536_INPUT) & PCA9536_PIN_MASK;
}

/**
 * 读取一个引脚
 * @param pin 引脚号
 * @return 引脚状态
 */
uint8_t BULLM_PCA9536::readPin(uint8_t pin) {
    if (pin > PCA9536_MAX_PIN) return 0;
    uint8_t input = readPort();
    return (input >> pin) & 0x01;
}

/**
 * 写4位输出端口
 * @param data 数据
 * @return 是否成功
 */
bool BULLM_PCA9536::writePort(uint8_t data) {
    return writeRegister(PCA9536_OUTPUT, data & PCA9536_PIN_MASK);
}

/**
 * 写一个引脚
 * @param pin 引脚号
 * @param state 引脚状态
 * @return 是否成功
 */
bool BULLM_PCA9536::writePin(uint8_t pin, bool state) {
    if (pin > PCA9536_MAX_PIN) return false;

    uint8_t output = readRegister(PCA9536_OUTPUT) & PCA9536_PIN_MASK;
    if (state) {
        output |= (1 << pin);
    } else {
        output &= ~(1 << pin);
    }
    return writePort(output);
}


/**
 * 设置引脚方向 (0 = 输出, 1 = 输入)
 * @param modes 引脚配置
 * @return 是否成功
 */
bool BULLM_PCA9536::setConfig(uint8_t modes) {
    return writeRegister(PCA9536_CONFIG, modes & PCA9536_PIN_MASK);
}

/**
 * 配置引脚方向 (0 = 输出, 1 = 输入)
 * @param pin 引脚号
 * @param mode 引脚模式
 * @return 是否成功
 */
bool BULLM_PCA9536::setConfigPin(uint8_t pin, uint8_t mode) {
    if (pin > PCA9536_MAX_PIN) return false;

    uint8_t config = readRegister(PCA9536_CONFIG) & PCA9536_PIN_MASK;
    if (mode) {
        config |= (1 << pin);
    } else {
        config &= ~(1 << pin);
    }
    return setConfig(config);
}

/**
 * 是否反转输入引脚极性 (0 = 正常, 1 = 反转)
 * @param reverses 引脚极性
 * @return
 */
bool BULLM_PCA9536::setPolarity(uint8_t reverses) {
    return writeRegister(PCA9536_POLARITY, reverses & PCA9536_PIN_MASK);
}

/**
 * 设置引脚极性 (0 = 正常, 1 = 反转)
 * @param pin 引脚号
 * @param reverse 引脚极性
 * @return 是否成功
 */
bool BULLM_PCA9536::setPolarityPin(uint8_t pin, uint8_t reverse) {
    if (pin > PCA9536_MAX_PIN) return false;

    uint8_t config = readRegister(PCA9536_POLARITY) & PCA9536_PIN_MASK;
    if (reverse) {
        config |= (1 << pin);
    } else {
        config &= ~(1 << pin);
    }
    return setPolarity(config);
}
