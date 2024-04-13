#include <Arduino.h>
#include <config/peripheralConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <tools/debugConfig.h>
#include <ibus.h>

void ibus_task(void* args)
{
    IBUS ibus(&UART1, 115200);

	for(;;)
	{
		ibus.update();
		//Serial.println(ibus.channels[2]);
		vTaskDelay(5 / portTICK_PERIOD_MS);
	}
}