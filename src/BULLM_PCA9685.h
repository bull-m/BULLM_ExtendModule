#ifndef BULLM_EXPAND_BULLM_PCA9685_H
#define BULLM_EXPAND_BULLM_PCA9685_H
#include <Arduino.h>
#include "BULLM_I2CDevice.h"


#define PCA9685_MODE1 0x00      // 模式寄存器1
#define PCA9685_MODE2 0x01      // 模式寄存器2

#define PCA9685_LED_START 0x06  // LED控制寄存器的开始
/**
 * // LED控制寄存器计算
 * ON_L: PCA9685_LED_START + 4 * index
 * ON_H: PCA9685_LED_START + 4 * index + 1
 * OFF_L: PCA9685_LED_START + 4 * index  + 2
 * OFF_H: PCA9685_LED_START + 4 * index  + 3
 */
#define PCA9685_PRE_SCALE 0xFE    // PWM输出频率的预分频器


#define MODE1_SLEEP 0b00010000  // 低功耗模式。振荡器关闭
#define MODE1_AI 0b00100000      // 自动增量，控制寄存器在读取或写入后会自动递增。这允许用户对寄存器进行顺序编程。
#define MODE1_RESTART 0b10000000  // 重新启动

#define MODE2_OUTDRV 0b100 // 输出驱动方式, 0: open drain, 1: totem pole

#define PCA9685_FREQUENCY_OSCILLATOR 25000000 // 振荡器时钟频率为25MHz：

#define PCA9685_PRESCALE_MIN 3   // 最小预标度值
#define PCA9685_PRESCALE_MAX 255 // 最大预缩放值


class BULLM_PCA9685 {
public:
    BULLM_PCA9685();
    BULLM_PCA9685(uint8_t addr);
    BULLM_PCA9685(uint8_t addr, TwoWire &i2c);
    ~BULLM_PCA9685();
    bool begin();
    uint8_t read(uint8_t reg);
    bool write(uint8_t reg, uint8_t data);
    void reset();
    // 设置频率
    bool setFreq(uint16_t freq);
    // 设置PWM占空比
    bool setPwm(uint8_t pin, uint8_t duty_cycle);
    bool setPwmHigh(uint8_t pin, uint16_t duty_cycle);
    bool setPwm(uint8_t pin, uint16_t on, uint16_t off);
    BULLM_I2CDevice *i2cDevice = nullptr;

private:
    uint8_t i2caddr = 0;
    TwoWire *i2c = nullptr;
};


#endif //BULLM_EXPAND_BULLM_PCA9685_H
