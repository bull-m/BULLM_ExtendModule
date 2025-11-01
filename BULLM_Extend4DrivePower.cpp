#include "BULLM_Extend4DrivePower.h"

BULLM_Extend4DrivePower::BULLM_Extend4DrivePower()
        : address(0x7F), i2c(&Wire) {}

BULLM_Extend4DrivePower::BULLM_Extend4DrivePower(const uint8_t addr)
        : address(addr), i2c(&Wire) {}

BULLM_Extend4DrivePower::BULLM_Extend4DrivePower(const uint8_t addr, TwoWire &i2c)
        : address(addr), i2c(&i2c) {}

BULLM_Extend4DrivePower::~BULLM_Extend4DrivePower() {
    if (pca9685) delete pca9685;
    pca9685 = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_Extend4DrivePower::begin() {
    if (pca9685) delete pca9685;
    pca9685 = new BULLM_PCA9685(address, *i2c);
    return pca9685->begin();
}

/**
 * 驱动指定电机
 * @param index 操作的电机,从0到3
 * @param value -255 ~ 255 负数反转，正数正转，0停止
 * @return
 */
bool BULLM_Extend4DrivePower::setSpeed(uint8_t index, int value, bool isBrake) {
    return setSpeedHigh(index, value * 16.06, isBrake);
}

/**
 *  驱动指定电机,高精度
 *  @param  index 操作的电机,从0到3
 *  @param  value -4096 ~ 4096 负数反转，正数正转，0停止
 */
bool BULLM_Extend4DrivePower::setSpeedHigh(uint8_t index, int value, bool isBrake){
    if(index >= 4) return false;
    if(value < -4095) value = -4095;
    if(value > 4095) value = 4095;
    /*
     * 前进引脚和后退引脚
     * 电机0：L_EN: 5, L_PWM: 4, R_EN: 2, R_PWM: 3
     * 电机1：L_EN: 0, L_PWM: 1, R_EN: 7, R_PWM: 6
     * 电机2：L_EN: 10, L_PWM: 8, R_EN: 14, R_PWM: 12
     * 电机3：L_EN: 13, L_PWM: 15, R_EN: 9, R_PWM: 11
     */
    // 根据index获取对应的引脚
    uint8_t L_EN, L_PWM, R_EN, R_PWM;
    switch (index) {
        case 0:
            L_EN = 5;
            L_PWM = 4;
            R_EN = 2;
            R_PWM = 3;
            break;
        case 1:
            L_EN = 0;
            L_PWM = 1;
            R_EN = 7;
            R_PWM = 6;
            break;
        case 2:
            L_EN = 10;
            L_PWM = 8;
            R_EN = 14;
            R_PWM = 12;
            break;
        case 3:
            L_EN = 13;
            L_PWM = 15;
            R_EN = 9;
            R_PWM = 11;
            break;
        default:
            return false;
    }
    // 刹车需要保持启用状态
    bool enable = value != 0 || isBrake;
    pca9685->setPwmHigh(L_EN, enable ? 4095 : 0);
    pca9685->setPwmHigh(R_EN, enable ? 4095 : 0);
    pca9685->setPwmHigh(L_PWM, value < 0 ? -value : 0);
    return pca9685->setPwmHigh(R_PWM, value > 0 ? value : 0);
}

/**
 * 刹车
 * @param index 操作的电机,从0到3
 */
bool BULLM_Extend4DrivePower::brake(uint8_t index) {
    return setSpeedHigh(index, 0,  true);
}

/**
 * 关闭所有电机
 */
bool BULLM_Extend4DrivePower::closeAll() {
    const uint8_t len = 4 * 16 + 1;
    uint8_t buffer[len];
    for (int i = 0; i < len; i++) {
        buffer[i] = 0;
    }
    buffer[0] = PCA9685_LED_START;
    // 直接操作寄存器
    return pca9685->i2cDevice->write(buffer, len);
}