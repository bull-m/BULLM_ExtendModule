
#ifndef BULLM_EXPAND_BULLM_EXTEND8RELAY_H
#define BULLM_EXPAND_BULLM_EXTEND8RELAY_H
#include "src/BULLM_I2CDevice.h"
#include "src/BULLM_PCA9555.h"

#define EXTEND8RELAY_PIN_MODE_INPUT 0xff
#define EXTEND8RELAY_PIN_MODE_OUTPUT 0

class BULLM_Extend8Relay {
public:
    BULLM_Extend8Relay();
    BULLM_Extend8Relay(uint8_t addr);
    BULLM_Extend8Relay(uint8_t addr, TwoWire &i2c);
    ~BULLM_Extend8Relay();
    bool begin();

    bool closeAllRelay();
    bool openAllRelay();
    bool setRelay(uint8_t pin, bool state);
    bool setRelayAll(uint8_t states);
    bool getRelay(uint8_t pin);
    uint8_t getRelayAll();

    bool setPinMode(uint8_t pin, uint8_t mode);
    bool setPinModeAll(uint8_t modes);
    uint8_t getInput(uint8_t pin);
    uint8_t getInputAll();
    bool setOutput(uint8_t pin, bool state);
    bool setOutputAll(uint8_t states);

private:
    BULLM_PCA9555 *pca9555 = nullptr;
    uint8_t address;
    TwoWire *i2c = nullptr;
};


#endif //BULLM_EXPAND_BULLM_EXTEND8RELAY_H
