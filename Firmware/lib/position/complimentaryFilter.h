#ifndef COMPLIMENTARYFILTER_H_
#define COMPLIMENTARYFILTER_H_
#include "Arduino.h"

class complimentaryFilter {
    public: 
        complimentaryFilter(float alpha);
        void init();
        void update(float gyroX, float gyroY, float gyroZ, float accelX, float accelY, float accelZ);
        double pitch, roll, yaw;
    private:
        float _alpha;
        long lastTime, currentTime;
        int delay;
        double dt;
        double accelPitch, accelRoll;
        double gyroRoll, gyroPitch, gyroYaw;
        
};


#endif