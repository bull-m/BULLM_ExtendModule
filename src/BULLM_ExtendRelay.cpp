#include "BULLM_ExtendRelay.h"

BULLM_ExtendRelay::BULLM_ExtendRelay() {
    pca9536 = new BULLM_PCA9536();
}

BULLM_ExtendRelay::BULLM_ExtendRelay(const uint8_t addr){
    pca9536 = new BULLM_PCA9536(addr);
}

BULLM_ExtendRelay::BULLM_ExtendRelay(const uint8_t addr, TwoWire &i2c) {
    pca9536 = new BULLM_PCA9536(addr, i2c);
}

BULLM_ExtendRelay::~BULLM_ExtendRelay() {
    if (pca9536) delete pca9536;
    pca9536 = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendRelay::begin() {
    if (!pca9536->begin()) return false;
    pca9536->setConfig(0b00000000); // 全为输出
    return true;
}

/*!
 *  @brief  关闭所有输出
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendRelay::closeAllRelay() {
    return pca9536->writePort(0b00000000);
}

/*!
 *  @brief  打开所有输出
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendRelay::openAllRelay() {
    return pca9536->writePort(0b11111111);
}

/*!
 *  @brief  设置继电器状态
 *  @param  pin
 *  @param  state
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendRelay::setRelay(uint8_t pin, bool state) {
    return pca9536->writePin(pin, state);
}

/*!
 *  @brief  设置所有继电器状态
 *  @param  state
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendRelay::setRelayAll(uint8_t states) {
    return pca9536->writePort(states);
}

/*!
*  @brief  从继电器获取一个继电器状态
*  @param  pin
*  @return 继电器状态
*/
bool BULLM_ExtendRelay::getRelay(uint8_t pin) {
    return pca9536->readPin(pin);
}

/*!
 *  @brief  获取所有继电器状态
 *  @return 所有继电器状态
 */
uint8_t BULLM_ExtendRelay::getRelayAll() {
    return pca9536->readPort();
}
