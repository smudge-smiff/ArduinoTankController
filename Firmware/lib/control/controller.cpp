#include <controller.h>
void Controller::init()
{
    //_leftMotor.attach(M2);
    //_leftMotor.writeMicroseconds(M2_Mid_Point);
    //_rightMotor.attach(M1);
    //_rightMotor.writeMicroseconds(M1_Mid_Point);
    analogWrite(M1_Forward, 0);
    analogWrite(M1_Aft, 0);
    analogWrite(M2_Forward, 0);
    analogWrite(M2_Aft, 0);
}
void Controller::run()
{
    for (;;)
    {
        updateRcData();
        rescaleRcCommand();
        calculateMode();
        if (previousMode != Mode)
        {
            initController();
        }
        updateController();
        calculateMotorOutputs();
        motorRescaleOutputs();
        motorSmoothing();
        motorOutput();
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}
void Controller::initController()
{

    switch (Mode)
    {
    case STOP:
        _cutOffMode.init();
        break;
    case MANUAL:
        _manualMode.init();
        break;
    }
}
void Controller::updateController()
{
    switch (Mode)
    {
    case STOP:
        _cutOffMode.update(scaledThrottleCommand, scaledSteeringCommand, &processedThrottleCommand, &processedSteeringCommand);
        break;
    case MANUAL:
        // varDEBUG(_RcStruct.channels[throttleChannel]);
        Serial.println("Man");
        _manualMode.update(scaledThrottleCommand, scaledSteeringCommand, &processedThrottleCommand, &processedSteeringCommand);
        // varDEBUG(processedThrottleCommand);
        /*Serial.print(processedThrottleCommand);
        Serial.print(" ");
        Serial.println(processedSteeringCommand);*/
        break;
    }
}
void Controller::updateRcData()
{
    xSemaphoreTake(ibusVarMutex, portMAX_DELAY);
    memcpy(&_RcStruct, &ibusRX, sizeof(_RcStruct));
    xSemaphoreGive(ibusVarMutex);
}
