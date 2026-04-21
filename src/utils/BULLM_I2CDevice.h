/**
 * This is a helper library to abstract away I2C, SPI, and 'generic transport' (e.g. UART) transactions and registers
 * Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!
 */

/**
 * 该类基于Adafruit_BusIO二次修改而来，他们使用了MIT许可，上方文本按源库作者要求保留，感谢Adafruit的开源工作。
 *
 * 这是一个辅助类，用于简化I2C的通信
 *
 * 对于Arduino UNO，这是SCL->5，SDA->4。
 */
#ifndef BULLM_I2CDEVICE_H
#define BULLM_I2CDEVICE_H

#include <Arduino.h>
#include <Wire.h>

class BULLM_I2CDevice {
public:
    BULLM_I2CDevice(uint8_t address, TwoWire &i2c);

    // 扫描指定的地址
    static bool scan(uint8_t address, TwoWire *i2c = &Wire);

    uint8_t address;
    bool begin(bool is_scan = true);
    void end(void);
    bool detection(void);

    bool read(uint8_t *buffer, size_t len, bool stop = true);
    bool write(const uint8_t *buffer, size_t len, bool stop = true);
    bool write_then_read(const uint8_t *write_buffer, size_t write_len,
                         uint8_t *read_buffer, size_t read_len,
                         bool stop = false);
    bool setSpeed(uint32_t desiredclk);

    size_t maxBufferSize; // 一个事务中可以读取多少字节

private:
    TwoWire *_wire;
    bool _begun;
    bool _read(uint8_t *buffer, size_t len, bool stop);
};


#endif //BULLM_I2CDEVICE_H
