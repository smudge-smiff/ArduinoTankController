#include <Arduino.h>
#include <config/peripheralConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include <tools/debugConfig.h>
#include <ibus.h>
#include <Servo.h>

void control_task(void* args)
{
    Servo Motor1;
	Servo Motor2;
	int val = 700;
    Motor1.attach(M1);
	Motor2.attach(M2);
	for(;;)
	{
		xSemaphoreTake(ibusVarMutex, portMAX_DELAY);
		varDEBUG(ibusRX.channels[4]);
		uint16_t safety = ibusRX.channels[4];
		uint16_t throttleCommandL = ibusRX.channels[2];
		uint16_t throttleCommandR = ibusRX.channels[1];
		xSemaphoreGive(ibusVarMutex);
		if (safety > 1500){
			Motor1.writeMicroseconds(throttleCommandR);
			Motor2.writeMicroseconds(throttleCommandL);
		}
		else {
			Motor1.writeMicroseconds(1300);
			Motor2.writeMicroseconds(1300);
		}
		//Motor1.writeMicroseconds(throttleCommandR);
		//Motor2.writeMicroseconds(throttleCommandL);
		//val++;
		//varDEBUG(val);
		vTaskDelay(50 / portTICK_PERIOD_MS);
	}
}