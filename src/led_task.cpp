#include <Arduino.h>
#include <config/peripheralConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>

#include <tools/debugConfig.h>

void led_task(void* args)
{
	pinMode(ON_BOARD_LED, OUTPUT);

	for(;;)
	{
		digitalWrite(ON_BOARD_LED, LOW);
		vTaskDelay(1000);
		digitalWrite(ON_BOARD_LED, HIGH);
		vTaskDelay(1000);
	}
}