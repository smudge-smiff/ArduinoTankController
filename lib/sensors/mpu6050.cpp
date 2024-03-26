#include "mpu6050.h"
#include "i2cHelper.h"
#include <config/peripheralConfig.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>
MPU6050::MPU6050(uint8_t addr)
{
    _addr = addr;
}
void MPU6050::init()
{
    setupRegisters();
    calibrate();
}
void MPU6050::setupRegisters()
{
    //Wake up
    i2cHelper::writeByte(_addr, 0x6B, 0x00);
    // Configure Accel
    // Wire.write; 2g --> 0x00, 4g --> 0x08, 8g --> 0x10, 16g --> 0x18
    i2cHelper::writeByte(_addr, 0x1C, MPU6050_ACCEL_SENSITIVITY);
    // Configure GYRO
    // 250 deg/s --> 0x00, 500 deg/s --> 0x08, 1000 deg/s --> 0x10, 2000 deg/s --> 0x18
    i2cHelper::writeByte(_addr, 0x1B, MPU6050_GYRO_SENSITIVITY);
}
void MPU6050::calibrate(){
    DEBUG("Entering Initilisation State");
    for(int calibrationCount = 0; calibrationCount < MPU6050_CALIBRATION_SAMPLES; calibrationCount++){
        readRegisters();
        applyConversion();
        gyroXCal += gyroX;
        gyroYCal += gyroY;
        gyroZCal += gyroZ;
        //varDEBUG(gyroXCal);
        vTaskDelay(3 / portTICK_PERIOD_MS);
        //DEBUG(".");
    }
    gyroXCal /= MPU6050_CALIBRATION_SAMPLES;
    gyroYCal /= MPU6050_CALIBRATION_SAMPLES;
    gyroZCal /= MPU6050_CALIBRATION_SAMPLES;
    //varDEBUG(gyroXCal);
    
}
void MPU6050::readRegisters(){
    uint8_t data[14]={0};
    //DEBUG("Initial:");
    //DEBUG_HEX(data[7]);
    i2cHelper::readBytes(_addr, 0x3B, data, 14);
    //DEBUG("Final:");
    //DEBUG_HEX(data[7]);
    rawAccelX = data[0] << 8 | data[1];
    rawAccelY = data[2] << 8 | data[3];
    rawAccelZ = data[4] << 8 | data[5];
    rawTemperature = data[6] << 8 | data[7];
    rawGryoX = data[8] << 8 | data[9];
    rawGyroY = data[10] << 8 | data[11];
    rawGyroZ = data[12] << 8 | data[13];
    //varDEBUG(rawGyroY);
}
void MPU6050::update()
{
    readRegisters();
    applyConversion();
    applyCalibration();
}
void MPU6050::applyConversion(){
    accelX = rawAccelX / MPU6050_ACCEL_CONVERSION;
    accelY = rawAccelY / MPU6050_ACCEL_CONVERSION;
    accelZ = rawAccelZ / MPU6050_ACCEL_CONVERSION;
    temperature = (rawTemperature/340.0)+36.53;
    gyroX = rawGryoX / MPU6050_GYRO_CONVERSION;
    gyroY = rawGyroY / MPU6050_GYRO_CONVERSION;
    gyroZ = rawGyroZ / MPU6050_GYRO_CONVERSION;
    //varDEBUG(gyroX);
    //varDEBUG(gyroZ);
    //vTaskDelay(1000 / portTICK_PERIOD_MS);

}
void MPU6050::applyCalibration(){
    calibratedGyroX = gyroX - gyroXCal;
    calibratedGyroY = gyroY - gyroYCal;
    calibratedGyroZ = gyroZ - gyroZCal;
    //varDEBUG(gyroXCal);
    //varDEBUG(calibratedGyroX);
}