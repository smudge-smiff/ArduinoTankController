#ifndef controller_H_
#define controller_H_

#include <Arduino.h>
#include <tools/debugConfig.h>
class Controller
{       // The class
    public: // Access specifier
        Controller(){};
        void init();
        void update();
        void outputSmoothing();
        void modeSelection();

    private:
        enum controlMode { STOP, MANUAL, RTH};
        controlMode Mode;
        long RTH_Longitude;
        long RTH_Latitude;

};
#endif