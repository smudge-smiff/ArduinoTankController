#ifndef STM32F401CC_H_
#define STM32F401CC_H_

// UART PIN Mappings
#define UART1_RX PA10
#define UART1_TX PA9
#define UART2_RX PA3
#define UART2_TX PA2
#define UART6_RX PA12
#define UART6_TX PA11
/*
    I2C
*/
#define I2C1_SDA PB7
#define I2C1_SCL PB6
/*
    SPI
*/
#define SPI_SCLK PA5
#define SPI_MOSI PA7
#define SPI_MISO PA6
// GPS UART
//#define gpsSerial UART2
#define gpsBaud 115200

// TELEM RADIO UART
//#define radioSerial UART6
//#define radioBaud 38400

// SBUS RECIEVER UART
#define sbusSerial UART1
#define sbusBaud 115200


// Discrete Outputs
#define ON_BOARD_LED PC13

// Discrete Inputs

/*
    I2C Config
*/
#define SET_I2C_HIGH_SPEED
#define I2C_TIMEOUT 100


/*
    Sensor Settings
*/
#define IMU1 MPU6050
#define IMU1_INTERFACE I2C1
#define IMU1_I2C_ADDRESS 0x68

//#define USE_IMU2
#ifdef USE_IMU2
    #define IMU2 MPU6050
    #define IMU2_INTERFACE I2C1
    #define IMU2_I2C_ADDRESS 0x69
#endif

// 2g --> 0x00, 4g --> 0x08, 8g --> 0x10, 16g --> 0x18
#define MPU6050_ACCEL_SENSITIVITY 0x08
#define MPU6050_ACCEL_CONVERSION 8192.0
// 250 deg/s --> 0x00, 500 deg/s --> 0x08, 1000 deg/s --> 0x10, 2000 deg/s --> 0x18
#define MPU6050_GYRO_SENSITIVITY 0x08
#define MPU6050_GYRO_CONVERSION 65.5

#define MPU6050_CALIBRATION_SAMPLES 500
#define ATTITUDE_UPDATE_FREQUENCY 200
#define COMPLIMENTARY_FILTER_ALPHA 0.98

#define PRESS_SENSE BMP280
#define PRESS_SENSE_INTERFACE I2C1
#define PRESS_SENSE_I2C_ADDRESS 0x76

#define COMPASS HM388L
#define COMPASS_INTERFACE I2C1
#define COMPASS_I2C_ADDRESS 0x31
//#define IMU1 MPU95000
#define IMU2_I2C_ADDRESS 0x69

// GPS
#define GPS_UPDATE_FREQUENCY 10
#define MINIMUM_SATELLITES_ARMING 6


/*
    Motor Outputs
*/
//#define M1 PB8
//#define M2 PB9
//#define M3 PB10
//#define M4 PA8

#define M1_Forward PB9
#define M1_Aft PB8
#define M2_Forward PB10
#define M2_Aft PA8
/*
    Motor Limits
*/
// Left Motor`
//#define M1_Lower_Limit 750
//#define M1_Mid_Point 1300
//#define M1_Upper_Limit 1850

// Right Motor
//#define M2_Lower_Limit 1000
//#define M2_Mid_Point 1500
//#define M2_Upper_Limit 2000

#endif

