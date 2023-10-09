#ifndef peripheralConfig_H_
#define peripheralConfig_H_

#include "config/pinMap/pinMap.h"
// UART PORTS
static HardwareSerial UART1(UART1_RX, UART1_TX);
static HardwareSerial UART2(UART2_RX, UART2_TX);
static HardwareSerial UART6(UART6_RX, UART6_TX);;

#ifdef SET_I2C_HIGH_SPEED
    #define I2C_SPEED 400000 
#else
    #define I2C_SPEED 100000 
#endif 
#define CONFIGURE_I2C() Wire.setSDA(I2C1_SDA); Wire.setSCL(I2C1_SCL); Wire.setClock(I2C_SPEED);

#endif