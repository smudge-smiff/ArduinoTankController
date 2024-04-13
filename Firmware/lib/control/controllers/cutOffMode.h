#ifndef CutOffMode_H_
#define CutOffMode_H_

#include <Arduino.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>

class CutOffMode
{       // The class
    public: // Access specifier
        CutOffMode(){};
        void init();
        void update(double scaledThrottleCommand, double scaledSteeringCommand, double* processedThrottleCommand, double* processedSteeringCommand);


};
#endif