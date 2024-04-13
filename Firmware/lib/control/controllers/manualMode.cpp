#include <controllers/manualMode.h>

void ManualMode::init(){

}
void ManualMode::update(double scaledThrottleCommand, double scaledSteeringCommand, double* processedThrottleCommand, double* processedSteeringCommand){
    *processedThrottleCommand = scaledThrottleCommand;
    *processedSteeringCommand = scaledSteeringCommand;

}
