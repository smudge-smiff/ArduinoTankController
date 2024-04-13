#include "Arduino.h"
#include "complimentaryFilter.h"
#include <config/peripheralConfig.h>
#include <config/peripheralConfig.h>
#include <tools/debugConfig.h>
#include <STM32FreeRTOS.h>

complimentaryFilter::complimentaryFilter(float alpha){
    _alpha = alpha;
}
void complimentaryFilter::init(){
    lastTime = micros();
}
void complimentaryFilter::update(float gyroX, float gyroY, float gyroZ, float accelX, float accelY, float accelZ){
    currentTime = micros();
    dt = (currentTime - lastTime) * 1e-6;// micros 0.0060
    lastTime = currentTime;
    //Serial.println(dt,4);

    accelPitch = atan2(accelY, accelZ) * RAD_TO_DEG;
    accelRoll = atan2(accelX, accelZ) * RAD_TO_DEG;

    gyroPitch = gyroX*dt;
    gyroRoll = gyroY*dt;
    gyroYaw = gyroZ*dt;

    pitch = (_alpha)*(pitch + gyroPitch) + (1-_alpha)*(accelPitch);
    roll = (_alpha)*(roll - gyroRoll) + (1-_alpha)*(accelRoll);

    yaw += gyroYaw;
    //varDEBUG(yaw);
}