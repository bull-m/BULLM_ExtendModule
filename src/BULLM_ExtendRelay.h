
#ifndef BULLM_EXTEND_RELAY_H
#define BULLM_EXTEND_RELAY_H
#include "utils/BULLM_I2CDevice.h"
#include "utils/BULLM_PCA9536.h"

class BULLM_ExtendRelay {
public:
    BULLM_ExtendRelay();
    BULLM_ExtendRelay(uint8_t addr);
    BULLM_ExtendRelay(uint8_t addr, TwoWire &i2c);
    ~BULLM_ExtendRelay();
    bool begin();

    bool closeAllRelay();
    bool openAllRelay();
    bool setRelay(uint8_t pin, bool state);
    bool setRelayAll(uint8_t states);
    bool getRelay(uint8_t pin);
    uint8_t getRelayAll();

private:
    BULLM_PCA9536 *pca9536;
};


#endif //BULLM_EXTEND_RELAY_H
