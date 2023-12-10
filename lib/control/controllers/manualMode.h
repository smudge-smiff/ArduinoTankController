#ifndef ManualMode_H_
#define ManualMode_H_

#include <Arduino.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>

class ManualMode
{       // The class
    public: // Access specifier
        ManualMode(){};
        void init();
        void update(double scaledThrottleCommand, double scaledSteeringCommand, double* processedThrottleCommand, double* processedSteeringCommand);


};
#endif