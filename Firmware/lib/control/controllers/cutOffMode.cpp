#include <controllers/cutOffMode.h>

void CutOffMode::init(){

}
void CutOffMode::update(double scaledThrottleCommand, double scaledSteeringCommand, double* processedThrottleCommand, double* processedSteeringCommand){
    *processedSteeringCommand = 0;
    *processedThrottleCommand = 0;
}