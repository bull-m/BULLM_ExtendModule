#include "BULLM_ExtendMos16.h"

BULLM_ExtendMos16::BULLM_ExtendMos16()
        : address(0x7F), i2c(&Wire) {}

BULLM_ExtendMos16::BULLM_ExtendMos16(const uint8_t addr)
        : address(addr), i2c(&Wire) {}

BULLM_ExtendMos16::BULLM_ExtendMos16(const uint8_t addr, TwoWire &i2c)
        : address(addr), i2c(&i2c) {}

BULLM_ExtendMos16::~BULLM_ExtendMos16() {
    if (pca9685) delete pca9685;
    pca9685 = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendMos16::begin() {
    if (pca9685) delete pca9685;
    pca9685 = new BULLM_PCA9685(address, *i2c);
    return pca9685->begin();
}

/*!
 *  @brief  为整个芯片设置PWM频率，最高可达1.6 KHz
 *  @param  freq 尝试匹配的浮点频率
 */
void BULLM_ExtendMos16::setPWMFreq(float freq) {
    pca9685->setFreq(freq);
}

/**
 * 驱动指定MOSx
 * @param index 操作的电机,从0到15
 * @param value 0 ~ 255 0停止
 * @return
 */
bool BULLM_ExtendMos16::setSpeed(uint8_t index, uint8_t value) {
    return setSpeedHigh(index, value * 16.06);
}

/**
 *  驱动指定MOS,高精度
 *  @param  index 操作的MOS,从0到15
 *  @param  value 0 ~ 4096 0停止
 */
bool BULLM_ExtendMos16::setSpeedHigh(uint8_t index, uint16_t value){
    if(index >= 16) return false;
    return pca9685->setPwmHigh(index, value);
}

/**
 * 关闭所有MOS
 */
bool BULLM_ExtendMos16::closeAll() {
    uint8_t success = 0;
    for (int i = 0; i < 16; ++i) {
        success += setSpeedHigh(i, 0);
    }
    return success == 16;
}