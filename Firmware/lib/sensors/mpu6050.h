#ifndef MPU6050_H_
#define MPU6050_H_
#include "Arduino.h"

class MPU6050{
    public:
        MPU6050(uint8_t addr);
        void init();
        void setupRegisters();
        void calibrate();
        void readRegisters();
        void update();
        void applyConversion();
        void applyCalibration();
        float calibratedGyroX, calibratedGyroY, calibratedGyroZ;
        float accelX, accelY, accelZ;
    private:
        uint8_t _addr;
        int16_t rawGryoX, rawGyroY, rawGyroZ;
        float gyroX, gyroY, gyroZ;
        int16_t rawTemperature;
        float temperature;
        int16_t rawAccelX, rawAccelY, rawAccelZ;
        double gyroXCal, gyroYCal, gyroZCal;
        
        
};
#endif