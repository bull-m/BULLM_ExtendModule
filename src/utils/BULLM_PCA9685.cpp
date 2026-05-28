#include "BULLM_PCA9685.h"

int mapRange(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

BULLM_PCA9685::BULLM_PCA9685() {
    i2cDevice = new BULLM_I2CDevice(0x7f, Wire);
}

BULLM_PCA9685::BULLM_PCA9685(const uint8_t addr) {
    i2cDevice = new BULLM_I2CDevice(addr, Wire);
}

BULLM_PCA9685::BULLM_PCA9685(const uint8_t addr, TwoWire &i2c) {
    i2cDevice = new BULLM_I2CDevice(addr, i2c);
}

BULLM_PCA9685::~BULLM_PCA9685() {
    delete i2cDevice;
    i2cDevice = nullptr;
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_PCA9685::begin() {
    if (!i2cDevice->begin()) return false;
    reset(); // 重新启动PCA9685
    setFreq(1000);
    return true;
}

// 在PCA9555读单个寄存器
uint8_t BULLM_PCA9685::read(uint8_t reg) {
    uint8_t buffer[1] = {reg};
    const bool res = i2cDevice->write_then_read(buffer, 1, buffer, 1);
    if (!res) {
        return 0;
    }
    return buffer[0];
}

// 向PCA9555写单个寄存器
bool BULLM_PCA9685::write(uint8_t reg, uint8_t data) {
    uint8_t buffer[2] = {reg, data};
    return i2cDevice->write(buffer, 2);
}

/**
 * 重新启动PCA9685
 */
void BULLM_PCA9685::reset() {
    write(PCA9685_MODE1, MODE1_RESTART);
    delay(10);
}

bool BULLM_PCA9685::setFreq(uint16_t freq) {
    if (freq < 1)
        freq = 1;
    if (freq > 3500)
        freq = 3500; // Datasheet limit is 3052=50MHz/(4*4096)
    float prescaleval = ((PCA9685_FREQUENCY_OSCILLATOR / (freq * 4096.0)) + 0.5) - 1;
    if (prescaleval < PCA9685_PRESCALE_MIN)
        prescaleval = PCA9685_PRESCALE_MIN;
    if (prescaleval > PCA9685_PRESCALE_MAX)
        prescaleval = PCA9685_PRESCALE_MAX;
    uint8_t prescale = (uint8_t) prescaleval;

    uint8_t oldmode = read(PCA9685_MODE1);
    uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // 睡眠
    write(PCA9685_MODE1, newmode);     //睡眠
    write(PCA9685_PRE_SCALE, prescale); // 设置预分频器
    write(PCA9685_MODE1, oldmode);
    delay(5);
    // 启用自动增量
    return write(PCA9685_MODE1, oldmode | MODE1_RESTART | MODE1_AI);
}


/*!
 *  @brief  Sets the PWM output of one of the PCA9685 pins
 *  @param  num One of the PWM output pins, from 0 to 15
 *  @param  on At what point in the 4096-part cycle to turn the PWM output ON
 *  @param  off At what point in the 4096-part cycle to turn the PWM output OFF
 *  @return 0 if successful, otherwise 1
 */
bool BULLM_PCA9685::setPwm(uint8_t pin, uint16_t on, uint16_t off) {
    if(pin >= 16) return false;
    uint8_t buffer[5];
    buffer[0] = PCA9685_LED_START + 4 * pin;
    buffer[1] = on;
    buffer[2] = on >> 8;
    buffer[3] = off;
    buffer[4] = off >> 8;

    return i2cDevice->write(buffer, 5);
}

/**
 * 设置占空比 0 ~ 255
 * @param pin
 * @param val 占空比
 * @return
 */
bool BULLM_PCA9685::setPwm(uint8_t pin, uint8_t val) {
    return setPwmRaw(pin, val * 4095.0 / 255.0);
}

/**
 * 设置占空比 0 ~ 4095
 * @param pin
 * @param val 占空比
 * @return
 */
bool BULLM_PCA9685::setPwmRaw(uint8_t pin, uint16_t val) {
    if(pin >= 16) return false;
    // 范围0和4095之间
    if (val > 4095) {
        val = 4095;
    }
    if (val == 0) {
        return setPwm(pin, 0, 4096); // 0%的占空比
    } else if (val == 4095) {
        return setPwm(pin, 4096, 0); // 100%的占空比
    } else {
        return setPwm(pin, 0, val);
    }
}

bool BULLM_PCA9685::closeAllPwm() {
    uint8_t buffer[17];
    uint8_t yes = 0;
    // 分4次更新
    for (int i = 0; i < 4; i++) {
        buffer[0] = PCA9685_LED_START + i * 4 * 4;
        for (int j = 0; j < 4; ++j) {
            buffer[1 + j * 4] = 0;
            buffer[2 + j * 4] = 0;
            buffer[3 + j * 4] = 255;
            buffer[4 + j * 4] = 4096 >> 8;
        }
        yes += i2cDevice->write(buffer, 17);
    }
    return yes == 4;
}
