#ifndef I2C_EEPROM_H_
#define I2C_EEPROM_H_

#include <Arduino.h>
#include <Wire.h>
#include <tools/debugConfig.h>
class I2C_EEPROM
{       // The class
    public: // Access specifier
        I2C_EEPROM(){};
        void write();
        void read();

    private:
        uint8_t _addr;
};
#endif