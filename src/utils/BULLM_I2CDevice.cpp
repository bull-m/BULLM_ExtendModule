
#include "BULLM_I2CDevice.h"

/**
 * 创建I2C设备
 * @param  _address I2C地址
 * @param  theWire 要使用的I2C总线
 */
BULLM_I2CDevice::BULLM_I2CDevice(uint8_t _address, TwoWire &i2c) {
    address = _address;
    _wire = &i2c;
    _begun = false;
#ifdef ARDUINO_ARCH_SAMD
    maxBufferSize = 250; // as defined in Wire.h's RingBuffer
#elif defined(ESP32)
    maxBufferSize = I2C_BUFFER_LENGTH;
#else
    maxBufferSize = 32;
#endif
}

/**
 * 初始化并执行基本地址检测
 * @param  is_scan 是否检测I2C地址是否可用，大部分的传感器能正常返回
 * @return I2C初始化成功，返回TRUE
 */
bool BULLM_I2CDevice::begin(bool is_scan) {
    _wire->begin();
    _begun = true;
    return !is_scan || detection();
}

/**
 * 取消初始化设备，关闭Wire接口
 */
void BULLM_I2CDevice::end(void) {
// 并非所有端口都实现 Wire::end()
#if !(defined(ESP8266) || \
      (defined(ARDUINO_ARCH_AVR) && !defined(WIRE_HAS_END)) || \
      defined(ARDUINO_ARCH_ESP32))
    _wire->end();
  _begun = false;
#endif
}

/**
 * 如果I2C初始化成功，并且找到具有该地址的设备，则返回True
 */
bool BULLM_I2CDevice::detection(void) {
    if (!_begun) {
        return false;
    }
    return scan(address, _wire);
}

/**
 * 向I2C设备写入数据
 * @param  buffer 要写入的数据缓冲区的数据
 * @param  len 要写入的长度
 * @param  stop 写入时是否发送I2C STOP信号
 * @return 是否成功
 */
bool BULLM_I2CDevice::write(const uint8_t *buffer, size_t len, bool stop) {
    if (len > maxBufferSize) {
        return false;
    }
    _wire->beginTransmission(address);
    // 写入数据
    if (_wire->write(buffer, len) != len) {
        return false; // 写入失败
    }
    return _wire->endTransmission(stop) == 0;
}

/**
 * 从I2C设备向缓冲区读取I2C数据，不能超过maxBufferSize字节。
 * @param  buffer 要读取的数据缓冲区
 * @param  len 要读取的字节数。
 * @param  stop 读取时是否发送I2C STOP信号
 * @return 是否成功
 */
bool BULLM_I2CDevice::read(uint8_t *buffer, size_t len, bool stop) {
    size_t pos = 0;
    while (pos < len) {
        // 要读取的字节数
        size_t read_len = ((len - pos) > maxBufferSize) ? maxBufferSize : (len - pos);
        bool read_stop = (pos >= len - read_len) && stop;;
        if (!_read(buffer + pos, read_len, read_stop))
            return false;
        pos += read_len;
    }
    return true;
}

bool BULLM_I2CDevice::_read(uint8_t *buffer, size_t len, bool stop) {
#if defined(TinyWireM_h)
    size_t recv = _wire->requestFrom((uint8_t)address, (uint8_t)len);
#elif defined(ARDUINO_ARCH_MEGAAVR)
    size_t recv = _wire->requestFrom(address, len, stop);
#else
    size_t recv = _wire->requestFrom((uint8_t) address, (uint8_t) len, (uint8_t) stop);
#endif

    // 没有足够的数据
    if (recv != len) return false;

    for (uint16_t i = 0; i < len; i++) {
        buffer[i] = _wire->read();
    }
    return true;
}

/**
 * 写入并读取一些数据
 * @param  write_buffer 要写入的数据缓冲区的数据
 * @param  write_len 要写入的长度
 * @param  read_buffer 要读取的数据缓冲区
 * @param  read_len 要读取的字节数
 * @param  stop 读取时是否发送I2C STOP信号
 * @return 是否成功
 */
bool BULLM_I2CDevice::write_then_read(const uint8_t *write_buffer,
                                      size_t write_len, uint8_t *read_buffer,
                                      size_t read_len, bool stop) {
    if (!write(write_buffer, write_len, stop)) {
        return false;
    }

    return read(read_buffer, read_len);
}

/**
 * 设置I2C时钟速度
 * @param frequency 频率
 * @return 是否成功
 */
bool BULLM_I2CDevice::setSpeed(uint32_t frequency) {
#if defined(__AVR_ATmega328__) || \
    defined(__AVR_ATmega328P__) // fix arduino core set clock
    // calculate TWBR correctly

  if ((F_CPU / 18) < frequency) {
      // 设置速度过高
    return false;
  }
  uint32_t atwbr = ((F_CPU / frequency) - 16) / 2;
  if (atwbr > 16320) {
      // 设置速度过底
    return false;
  }

  if (atwbr <= 255) {
    atwbr /= 1;
    TWSR = 0x0;
  } else if (atwbr <= 1020) {
    atwbr /= 4;
    TWSR = 0x1;
  } else if (atwbr <= 4080) {
    atwbr /= 16;
    TWSR = 0x2;
  } else { //  if (atwbr <= 16320)
    atwbr /= 64;
    TWSR = 0x3;
  }
  TWBR = atwbr;
  return true;
#elif (ARDUINO >= 157) && !defined(ARDUINO_STM32_FEATHER) && \
    !defined(TinyWireM_h)
    _wire->setClock(frequency);
    return true;
#else
    (void)frequency;
  return false;
#endif
}

///**
// * 扫描指定的地址是否存在，请确保I2C总线已初始化
// * @param address 地址
// * @param theWire 要使用的I2C总线
// * @return
// */
bool BULLM_I2CDevice::scan(uint8_t address, TwoWire *i2c) {
    i2c->beginTransmission(address);
#ifdef ARDUINO_ARCH_MBED
    i2c->write(0); // 强制执行写请求而不是读请求
#endif
    return i2c->endTransmission() == 0;
}