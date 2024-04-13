#ifndef i2cHelper_H_
#define i2cHelper_H_
#include <Arduino.h>

class i2cHelper
{
public:
  static void init(int SDA, int SCL, int freq);
  static void takeMutex();
  static void giveMutex();
  static void writeByte(uint8_t addr, uint8_t reg, uint8_t data);
  static void writeBytes(uint8_t addr, uint8_t reg, uint8_t data[], int length);
  static void readBytes(uint8_t addr, uint8_t reg, uint8_t data[], int number);
  static int16_t readInt16_t(uint8_t addr, uint8_t reg);
  static uint16_t readUint16_t(uint8_t addr, uint8_t reg);
  i2cHelper() = delete;

};

#endif