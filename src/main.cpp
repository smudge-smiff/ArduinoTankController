#include <Arduino.h>
#include <Wire.h>
#include <config/peripheralConfig.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include "semphr.h"
#include "i2cHelper.h"
#include "i2cScanner.h"

extern void control_task(void* args);
extern void led_task(void* args);
extern void ibus_task(void* args);
extern void altitude_task(void* args);
extern void attitude_task(void* args);

SemaphoreHandle_t ibusVarMutex;
ibusRXStruct ibusRX;
SemaphoreHandle_t i2cMutex;
SemaphoreHandle_t altitudeMutex;
altitudeStruct altitude;
attitudeStruct attitude;

void createTasks(){
  xTaskCreate(attitude_task, "altitude_task", configMINIMAL_STACK_SIZE * 10, NULL, 1, NULL);
  //xTaskCreate(altitude_task, "altitude_task", configMINIMAL_STACK_SIZE * 10, NULL, 1, NULL);
  //xTaskCreate(control_task, "control_task", configMINIMAL_STACK_SIZE * 10, NULL, 1, NULL);
  //xTaskCreate(led_task, "led_task", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);
  //xTaskCreate(ibus_task, "ibus_task", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);
}
void createMutex(){
  ibusVarMutex = xSemaphoreCreateMutex();
  i2cMutex = xSemaphoreCreateMutex();
  altitudeMutex = xSemaphoreCreateMutex();
}
void configurePeripherals(){
  i2cHelper::init(I2C1_SDA, I2C1_SCL, 400000 );
  #ifdef BUILD_DEBUG
    i2cScanner scanner = i2cScanner();
    scanner.scan();
  #endif

}

void setup()
{
  DEBUG_INIT()
  configurePeripherals();

  createTasks();
  createMutex();
  vTaskStartScheduler();
}


void loop(){} // Never reached

