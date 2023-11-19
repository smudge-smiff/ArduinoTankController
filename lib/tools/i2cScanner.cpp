#include "i2cScanner.h"

void i2cScanner::scan()
{
    byte error, address;
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            DEBUG("I2C device found at address 0x");
            if (address < 16)
                DEBUG("0");
            DEBUG_HEX(address)

            nDevices++;
        }
        else if (error == 4)
        {
            DEBUG("Unknown error at address 0x");
            if (address < 16)
                DEBUG("0");
            DEBUG_HEX(address);
        }
    }
    if (nDevices == 0)
        DEBUG("No I2C devices found\n");
    else
        DEBUG("done\n");
}