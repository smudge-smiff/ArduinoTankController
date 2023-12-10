#include <controller.h>
void Controller::rescaleRcCommand(){
   scaledThrottleCommand = mapToRange(_RcStruct.channels[throttleChannel], 988, 2007, -1.0, 1.0);
   scaledSteeringCommand = mapToRange(_RcStruct.channels[steeringChannel], 988, 2007, -1.0, 1.0);
}
double Controller::mapToRange(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}