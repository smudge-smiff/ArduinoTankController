#ifndef controller_H_
#define controller_H_

#include <Arduino.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include <controllers/manualMode.h>
#include <controllers/cutOffMode.h>
#include <Servo.h>
#include <config/peripheralConfig.h>

#define throttleChannel 1
#define steeringChannel 0
#define cutOffChannel 4
#define modeChannel 5

#define cutOffModeValue 2011
#define manualModeValue 988


class Controller
{       // The class
    public: // Access specifier
        Controller(){};
        void init();
        void run();

    private:
        void updateRcData();
        void calculateMode();
        void calculateMotorOutputs();
        double clampMotorOutputs(double command);
        void motorRescaleOutputs();
        void motorSmoothing();
        void motorOutput();
        void initController();
        void updateController();
        void rescaleRcCommand();
        double mapToRange(double x, double in_min, double in_max, double out_min, double out_max);
        ibusRXStruct _RcStruct;
        enum controlMode { STOP, MANUAL, RTH };
        controlMode Mode;
        controlMode previousMode;
        long RTH_Longitude;
        long RTH_Latitude;
        double scaledThrottleCommand; // 
        double scaledSteeringCommand; // Right is +ve
        double processedThrottleCommand; // 
        double processedSteeringCommand; // Right is +ve
        double processedLeftOutput;
        double processedRightOutput;
        int _leftOutput;
        int _leftOutputPrevious;
        int _rightOutput;
        int _rightOutputPrevious;
        ManualMode _manualMode;
        CutOffMode _cutOffMode;
        Servo _leftMotor;
        Servo _rightMotor;

};
#endif