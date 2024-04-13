#include "i2cHelper.h"
#include "Wire.h"
#include <STM32FreeRTOS.h>
#include <threadConnectorMutex.h>
#include <tools/debugConfig.h>
void i2cHelper::init(int SDA, int SCL, int freq){
    Wire.setSDA(SDA); 
    Wire.setSCL(SCL); 
    Wire.setClock(freq);
    Wire.begin();
    DEBUG("Init");
}
void i2cHelper::takeMutex(){
    xSemaphoreTake(i2cMutex, portMAX_DELAY);
}
void i2cHelper::giveMutex(){
    xSemaphoreGive(i2cMutex);
}
void i2cHelper::writeByte(uint8_t addr, uint8_t reg, uint8_t data){
    i2cHelper::takeMutex();

    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();

    i2cHelper::giveMutex();
}
void i2cHelper::writeBytes(uint8_t addr, uint8_t reg, uint8_t data[], int length){
    i2cHelper::takeMutex();

    Wire.beginTransmission(addr);
    Wire.write(reg);
    for (int i = 0; i <= length -1; i++) {
        Wire.write(data[i]);
    }

    Wire.endTransmission();

    i2cHelper::giveMutex();
}
void i2cHelper::readBytes(uint8_t addr, uint8_t reg, uint8_t data[], int number){
    i2cHelper::takeMutex();
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(addr, number);
    for (int i = 0; i <= number -1; i++) {
        if(Wire.available() > 0){
            data[i]=Wire.read();
        }
    }
    i2cHelper::giveMutex();
}
int16_t i2cHelper::readInt16_t(uint8_t addr, uint8_t reg){
    uint8_t read[2];
    i2cHelper::readBytes(addr, reg, read, 2);
    int16_t res = read[0] << 8 | read[1];
    return res;
}
uint16_t i2cHelper::readUint16_t(uint8_t addr, uint8_t reg){
    uint8_t read[2];
    i2cHelper::readBytes(addr, reg, read, 2);
    uint16_t res = read[0] << 8 | read[1];
    return res;
}