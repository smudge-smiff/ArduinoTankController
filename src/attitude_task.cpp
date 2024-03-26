#include <Arduino.h>
#include <config/peripheralConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include <mpu6050.h>
#include <complimentaryFilter.h>
#include <tools/debugConfig.h>
#include "i2cHelper.h"

void attitude_task(void* args)
{
	MPU6050 imu1(IMU1_I2C_ADDRESS);
	complimentaryFilter cf(COMPLIMENTARY_FILTER_ALPHA);
	int updateTime = 1000 / ATTITUDE_UPDATE_FREQUENCY; // ms
    imu1.init();
	cf.init();
    for(;;)
	{
		long start = micros();
		imu1.update();
		cf.update(imu1.calibratedGyroX, imu1.calibratedGyroY, imu1.calibratedGyroZ, imu1.accelX, imu1.accelY, imu1.accelZ);
		//Serial.println(updateTime);
		long end = micros();
		long dt = end - start; // us
		long del = updateTime - dt/1000;
		vTaskDelay(del / portTICK_PERIOD_MS);

	}
}