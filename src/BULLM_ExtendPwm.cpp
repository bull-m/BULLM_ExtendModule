#include "BULLM_ExtendPwm.h"

BULLM_ExtendPwm::BULLM_ExtendPwm() {
    pca9685 = new BULLM_PCA9685();
}

BULLM_ExtendPwm::BULLM_ExtendPwm(const uint8_t addr) {
    pca9685 = new BULLM_PCA9685(addr);
}

BULLM_ExtendPwm::BULLM_ExtendPwm(const uint8_t addr, TwoWire &i2c) {
    pca9685 = new BULLM_PCA9685(addr, i2c);
}

BULLM_ExtendPwm::~BULLM_ExtendPwm() {
    if (pca9685) delete pca9685;
    pca9685 = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendPwm::begin() {
    if (!pca9685) return false;
    return pca9685->begin();
}

/*!
 *  @brief  为整个芯片设置PWM频率，最高可达1.6 KHz
 *  @param  freq 尝试匹配的浮点频率
 */
bool BULLM_ExtendPwm::setPwmFreq(uint16_t freq) {
    return pca9685->setFreq(freq);
}

/**
 * 驱动指定MOSx
 * @param index 操作的电机,从0到15
 * @param value 0 ~ 255 0停止
 * @return
 */
bool BULLM_ExtendPwm::setPwm(uint8_t index, uint8_t value) {
    return pca9685->setPwm(index, value);
}

/**
 *  驱动指定MOS,高精度
 *  @param  index 操作的PWM,从0到15
 *  @param  value 0 ~ 4096 0停止
 */
bool BULLM_ExtendPwm::setPwmRaw(uint8_t index, uint16_t value) {
    return pca9685->setPwmRaw(index, value);
}

/**
 * 关闭所有PWM
 */
bool BULLM_ExtendPwm::closeAllPwm() {
    return pca9685->closeAllPwm();
}
