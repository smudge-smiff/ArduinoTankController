void I2C_EEPROM::write(uint8_t writeAddress, uint8_t *data, uint8_t len)
{
    Wire.beginTransmission(EEPROM_I2C_ADDRESS);
    Wire.write((writeAddress & 0xFF00) >> 8); // MSB
    Wire.write(writeAddress & 0x00FF);        // LSB
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        Wire.write(data[i]);
    }
    Wire.endTransmission();

    delay(5);
}

// Function to read from EEPROM
void I2C_EEPROM::read(uint8_t readAddress, uint8_t *data, uint8_t len)
{
    Wire.beginTransmission(EEPROM_I2C_ADDRESS);
    Wire.write((byte)(readAddress & 0xFF00) >> 8);
    Wire.write((byte)(readAddress & 0x00FF));
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_I2C_ADDRESS, len);
    int i;
    for (i = 0; i < len; i++)
    {
        if (Wire.available())
        {
            data[i] = Wire.read();
        }
    }
}