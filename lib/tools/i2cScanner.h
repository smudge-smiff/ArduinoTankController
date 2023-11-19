#ifndef i2cScanner_H_
#define i2cScanner_H_

#include <Arduino.h>
#include <Wire.h>
#include <tools/debugConfig.h>
class i2cScanner {       // The class
  public:             // Access specifier
    i2cScanner() {};
    void scan();
};
#endif