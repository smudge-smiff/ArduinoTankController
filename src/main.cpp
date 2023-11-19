#include <Arduino.h>
#include <Wire.h>
#include <config/peripheralConfig.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include "semphr.h"
#include "i2cScanner.h"

//void createTasks();
//void createMutex();
//void configurePeripherals();

extern void control_task(void* args);
extern void led_task(void* args);
extern void ibus_task(void* args);

SemaphoreHandle_t ibusVarMutex;
ibusRXStruct ibusRX;
void createTasks(){
  i2cScanner scanner = i2cScanner();
  scanner.scan();
  xTaskCreate(control_task, "control_task", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);
  xTaskCreate(led_task, "led_task", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);
  xTaskCreate(ibus_task, "ibus_task", configMINIMAL_STACK_SIZE * 3, NULL, 1, NULL);
}
void createMutex(){
  ibusVarMutex = xSemaphoreCreateMutex();
}
void configurePeripherals(){
  CONFIGURE_I2C()
  #ifdef BUILD_DEBUG
    i2cScanner scanner = i2cScanner();
    scanner.scan();
  #endif

}


void setup()
{
  DEBUG_INIT()
  

  createTasks();
  createMutex();
  vTaskStartScheduler();
}


void loop(){} // Never reached