#include <Arduino.h>
#include <controller.h>

void control_task(void* args)
{
	Controller controller;
	controller.init();
	controller.run();
}