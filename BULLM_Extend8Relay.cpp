

#include "BULLM_Extend8Relay.h"

BULLM_Extend8Relay::BULLM_Extend8Relay()
        : address(0x24), i2c(&Wire) {}

BULLM_Extend8Relay::BULLM_Extend8Relay(const uint8_t addr)
        : address(addr), i2c(&Wire) {}

BULLM_Extend8Relay::BULLM_Extend8Relay(const uint8_t addr, TwoWire &i2c)
        : address(addr), i2c(&i2c) {}

BULLM_Extend8Relay::~BULLM_Extend8Relay() {
    if (pca9555) delete pca9555;
    pca9555 = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_Extend8Relay::begin() {
    if (pca9555) delete pca9555;
    pca9555 = new BULLM_PCA9555(address, *i2c);

    bool res = pca9555->begin();
    if (!res) return res;
    pca9555->setConfig(0, 0b00000000); // 端口0全为输出
    pca9555->setConfig(1, 0b11111111); // 端口1全为输入
    return res;
}

/*!
 *  @brief  关闭所有输出
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_Extend8Relay::closeAllRelay() {
    return pca9555->writePort(0, 0b00000000);
}

/*!
 *  @brief  打开所有输出
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_Extend8Relay::openAllRelay() {
    return pca9555->writePort(0, 0b11111111);
}

/*!
 *  @brief  设置继电器状态
 *  @param  pin
 *  @param  state
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_Extend8Relay::setRelay(uint8_t pin, bool state) {
    return pca9555->writePin(0, pin, state);
}

/*!
 *  @brief  设置所有继电器状态
 *  @param  state
 *  @return 如果成功则为true，否则为false
 */
 bool BULLM_Extend8Relay::setRelayAll(uint8_t states) {
    return pca9555->writePort(0, states);
 }

 /*!
 *  @brief  从继电器获取一个继电器状态
 *  @param  pin
 *  @return 继电器状态
 */
bool BULLM_Extend8Relay::getRelay(uint8_t pin) {
     return pca9555->readPin(0, pin);
}

/*!
 *  @brief  获取所有继电器状态
 *  @return 所有继电器状态
 */
 uint8_t BULLM_Extend8Relay::getRelayAll() {
     return pca9555->readPort(0);
 }


/**
 * 设置引脚模式 (0 = 输出, 1 = 输入)
 * @param pin 引脚号
 * @param mode 引脚模式
 * @return 是否成功
 */
bool BULLM_Extend8Relay::setPinMode(uint8_t pin, uint8_t mode) {
    return pca9555->setConfigPin(1, pin, mode);
}

/**
 * 批量设置引脚模式 (0 = 输出, 1 = 输入)
 * @param modes 引脚模式
 * @return 是否成功
 */
bool BULLM_Extend8Relay::setPinModeAll(uint8_t modes) {
    return pca9555->setConfig(1, modes);
}

/**
 *  获取输入，只有配置为输入的引脚的值才有效
 *  @param  pin
 *  @return 输入值
 */
uint8_t BULLM_Extend8Relay::getInput(uint8_t pin) {
    return pca9555->readPin(1, pin);
}

/**
 * 批量获取输入，只有配置为输入的引脚的值才有效
 * @return 一个字节数据，每位对应一个引脚
 */
uint8_t BULLM_Extend8Relay::getInputAll() {
    return pca9555->readPort(1);
}

/**
 * 设置输出, 只对配置为输出的引脚有效
 * @param pin 引脚号
 * @param state 引脚状态
 * @return 是否成功
 */
bool BULLM_Extend8Relay::setOutput(uint8_t pin, bool state) {
    return pca9555->writePin(1, pin, state);
}

/**
 * 批量设置输出, 只对配置为输出的引脚有效
 * @param states 输出值
 * @return 是否成功
 */
bool BULLM_Extend8Relay::setOutputAll(uint8_t states) {
    return pca9555->writePort(1, states);
}

