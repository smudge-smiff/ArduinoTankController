#include <controller.h>
void Controller::calculateMode(){
    int16_t modeSelect = _RcStruct.channels[modeChannel];
    int16_t cutOff = _RcStruct.channels[cutOffChannel];

    previousMode = Mode;
    //Serial.println(cutOff);
    if (cutOff < cutOffModeValue){
        Mode = STOP;
        return;
    }
    //Serial.println(modeSelect);
    switch (modeSelect)
    {
        case 988:
            Mode = MANUAL;
            break;
        
        default:
            Mode = STOP;
            break;
    }
}