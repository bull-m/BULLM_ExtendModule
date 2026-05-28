#include "BULLM_ExtendMotor8.h"

BULLM_ExtendMotor8::BULLM_ExtendMotor8() {
    pca9685 = new BULLM_PCA9685();
}

BULLM_ExtendMotor8::BULLM_ExtendMotor8(const uint8_t addr) {
    pca9685 = new BULLM_PCA9685(addr);
}

BULLM_ExtendMotor8::BULLM_ExtendMotor8(const uint8_t addr, TwoWire &i2c) {
    pca9685 = new BULLM_PCA9685(addr, i2c);
}

BULLM_ExtendMotor8::~BULLM_ExtendMotor8() {
    delete pca9685;
    pca9685 = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendMotor8::begin() {
    if (!pca9685) return false;
    return pca9685->begin();
}

/*!
 *  @brief  为整个芯片设置PWM频率，最高可达1.6 KHz
 *  @param  freq 尝试匹配的浮点频率
 */
bool BULLM_ExtendMotor8::setPwmFreq(uint16_t freq) {
    return pca9685->setFreq(freq);
}

/**
 * 驱动指定电机
 * @param index 操作的电机,从0到3
 * @param value -255 ~ 255 负数反转，正数正转，0停止
 * @return
 */
bool BULLM_ExtendMotor8::setSpeed(uint8_t index, int value) {
    return setSpeedRaw(index, value * 4095.0 / 255.0);
}

/**
 *  驱动指定电机,高精度
 *  @param  index 操作的电机,从0到3
 *  @param  value -4096 ~ 4096 负数反转，正数正转，0停止
 */
bool BULLM_ExtendMotor8::setSpeedRaw(uint8_t index, int value) {
    if(index > 7) return false;
    if(value < -4095) value = -4095;
    if(value > 4095) value = 4095;
    /*
     * 前进引脚和后退引脚
     * 电机0：0脚和1脚
     * 电机1：2脚和3脚
     * 电机2：4脚和5脚
     * 电机3：6脚和7脚
     * 电机4：8脚和9脚
     * 电机5：10脚和11脚
     * 电机6：12脚和13脚
     * 电机7：14脚和15脚
     */
    const uint8_t forward_i = index * 2;
    const uint8_t reverse_i = index * 2 + 1;
    uint8_t success = 0;
    if(value >= 0){
        success += pca9685->setPwmRaw(forward_i, value);
        success += pca9685->setPwmRaw(reverse_i, 0);
    } else{
        success += pca9685->setPwmRaw(forward_i, 0);
        success += pca9685->setPwmRaw(reverse_i, -value);
    }
    return success == 4;
}

/**
 * 关闭所有电机
 */
bool BULLM_ExtendMotor8::closeAll() {
    return pca9685->closeAllPwm();
}
