//
// Created by yyz_n on 2025/9/9.
//

#include "BULLM_PCA9555.h"

BULLM_PCA9555::BULLM_PCA9555()
        : i2caddr(0x27), i2c(&Wire) {}

BULLM_PCA9555::BULLM_PCA9555(const uint8_t addr)
        : i2caddr(addr), i2c(&Wire) {}

BULLM_PCA9555::BULLM_PCA9555(const uint8_t addr, TwoWire &i2c)
        : i2caddr(addr), i2c(&i2c) {}

BULLM_PCA9555::~BULLM_PCA9555() {
    if (i2cDevice)
        delete i2cDevice;
    i2cDevice = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_PCA9555::begin() {
    if (i2cDevice)
        delete i2cDevice;
    i2cDevice = new BULLM_I2CDevice(i2caddr, *i2c);
    return i2cDevice->begin();
}

// 在PCA9555读单个寄存器
uint8_t BULLM_PCA9555::readRegister(uint8_t reg) {
    uint8_t buffer[1] = {reg};
    bool res = i2cDevice->write_then_read(buffer, 1, buffer, 1);
    if(!res){
        return 0;
    }
    return buffer[0];
}

// 向PCA9555写单个寄存器
bool BULLM_PCA9555::writeRegister(uint8_t reg, uint8_t data) {
    uint8_t buffer[2] = {reg, data};
    return i2cDevice->write(buffer, 2);
}

// 读取一个端口
uint8_t BULLM_PCA9555::readPort(uint8_t port) {
    if (port > 1) return 0;
    return readRegister(port == 0 ? PCA9555_INPUT0 : PCA9555_INPUT1);
}

/**
 * 读取一个引脚
 * @param port 端口号
 * @param pin 引脚号
 * @param isNoCache 是否不使用缓存
 * @return 引脚状态
 */
uint8_t BULLM_PCA9555::readPin(uint8_t port, uint8_t pin) {
    if (pin > 7) return 0;
    uint8_t input = readPort(port);
    return (input >> pin) & 0x01;
}

/**
 * 写一个端口
 * @param port 端口号
 * @param data 数据
 * @return 是否成功
 */
bool BULLM_PCA9555::writePort(uint8_t port, uint8_t data) {
    if (port > 1) return false;
    uint8_t reg = port == 0 ? PCA9555_OUTPUT0 : PCA9555_OUTPUT1;
    return writeRegister(reg, data);
}

/**
 * 写一个引脚
 * @param port 端口号
 * @param pin 引脚号
 * @param state 引脚状态
 * @return 是否成功
 */
bool BULLM_PCA9555::writePin(uint8_t port, uint8_t pin, bool state) {
    if (port > 1 || pin > 7) return false;
    uint8_t reg = port == 0 ? PCA9555_OUTPUT0 : PCA9555_OUTPUT1;
    uint8_t output = readRegister(reg);
    if (state) {
        output |= (1 << pin);  // 置位输出高电平
    } else {
        output &= ~(1 << pin); // 清零输出低电平
    }
    return writePort(port, output);
}


/**
 * 设置引脚方向 (0 = 输出, 1 = 输入)
 * @param port 端口号
 * @param config 引脚配置
 * @return 是否成功
 */
bool BULLM_PCA9555::setConfig(uint8_t port, uint8_t modes) {
    if (port > 1) return false;
    uint8_t reg = port == 0 ? PCA9555_CONFIG0 : PCA9555_CONFIG1;
    return writeRegister(reg, modes);
}

/**
 * 配置引脚方向 (0 = 输出, 1 = 输入)
 * @param port 端口号
 * @param pin 引脚号
 * @param mode 引脚模式
 * @return 是否成功
 */
bool BULLM_PCA9555::setConfigPin(uint8_t port, uint8_t pin, uint8_t mode) {
    if (port > 1 || pin > 7) return false;
    uint8_t reg = (port == 0) ? PCA9555_CONFIG0 : PCA9555_CONFIG1;
    uint8_t config = readRegister(reg);
    if (mode) {
        config |= (1 << pin);  // 置位输入
    } else {
        config &= ~(1 << pin); // 清零输出
    }
    return setConfig(port, config);
}
/**
 * 是否反转输入引脚极性 (0 = 正常, 1 = 反转)
 * @param port 端口号
 * @param polarity 引脚极性
 * @return
 */
bool BULLM_PCA9555::setPolarity(uint8_t port, uint8_t reverses) {
    if (port > 1) return false;
    uint8_t reg = (port == 0) ? PCA9555_POLARITY0 : PCA9555_POLARITY1;
    return writeRegister(reg, reverses);
}

/**
 * 设置引脚极性 (0 = 正常, 1 = 反转)
 * @param port 端口号
 * @param pin 引脚号
 * @param direction 引脚极性
 * @return 是否成功
 */
bool BULLM_PCA9555::setPolarityPin(uint8_t port, uint8_t pin, uint8_t reverse) {
    if (port > 1 || pin > 7) return false;
    uint8_t reg = (port == 0) ? PCA9555_POLARITY0 : PCA9555_POLARITY1;
    uint8_t config = readRegister(reg);
    if (reverse) {
        config |= (1 << pin);  // 置位反转
    } else {
        config &= ~(1 << pin); // 清零正常
    }
    return setPolarity(port, config);
}