#include <Arduino.h>
#include <config/peripheralConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include <bmp280.h>
#include <tools/debugConfig.h>
#include "i2cHelper.h"

uint8_t delayTime;
BMP280 bmp;
double T, P, Psl, Palt;
double h = 20;

void getTandP(){
    i2cHelper::takeMutex();
    delayTime = bmp.startMeasurment();
    i2cHelper::giveMutex();
    if(delayTime != 0){
	    vTaskDelay(delayTime / portTICK_PERIOD_MS);
    }else{
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    i2cHelper::takeMutex();
    bmp.getTemperatureAndPressure(T,P);
    i2cHelper::giveMutex();
}

void updateAltitudeStruct(){ 
    xSemaphoreTake(altitudeMutex, portMAX_DELAY);
    altitude.altitude = Palt;
    altitude.pressure = P;
    altitude.pressureSeaLevel = Psl;
    altitude.Temperature = T;
    altitude.lastUpdate = millis();
    xSemaphoreGive(altitudeMutex);
}
void altitude_task(void* args)
{
    bmp.begin();
    bmp.setOversampling(4);
    getTandP();
    Psl= bmp.sealevel(P, h);
    
    for(;;)
	{
        getTandP();
        Palt = bmp.altitude(P, Psl);
        
        updateAltitudeStruct();
        varDEBUG(altitude.altitude);
        vTaskDelay(100 / portTICK_PERIOD_MS);

	}
}