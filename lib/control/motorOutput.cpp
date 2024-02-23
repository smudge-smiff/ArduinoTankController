#include <controller.h>
/*
    The controller will calculate a throttle and steering command in the range of +/-1
    The motor rescale outputs function will remap this +/-1 range to the range the motor will accept
    The motor smoothing function, will momentarily return the individual motor output to the mid point 
    accepted by the ESC to prevent the ESC locking up 
    The motor outputsfunction will output the current throttle for each esc
*/
void Controller::calculateMotorOutputs(){
    processedLeftOutput = clampMotorOutputs(processedThrottleCommand + processedSteeringCommand);
    processedRightOutput = clampMotorOutputs(processedThrottleCommand - processedSteeringCommand);
    //Serial.print(processedLeftOutput);
    //Serial.print(" ");
    //Serial.println(processedRightOutput);
}
double Controller::clampMotorOutputs(double command){
    
    if (command > 1.0) {
        command = 1.0;
    }else if (command <-1.0){
        command = -1.0;
    }
    return command;
}
void Controller::motorRescaleOutputs(){
    _leftOutput= mapToRange(processedLeftOutput, -1.0, 1.0, -256, 256);
    _rightOutput= mapToRange(processedRightOutput, -1.0, 1.0, -256, 256);
    //Serial.println
    //varDEBUG(processedLeftOutput);
    /*Serial.print(_leftOutput);
    Serial.print(" ");
    Serial.println(_rightOutput);*/
}
void Controller::motorSmoothing(){

    
}
void Controller::motorOutput(){
    
    if (_leftOutput > 0){
        analogWrite(M1_Forward, _leftOutput);
        analogWrite(M1_Aft, 0);
    }else if (_leftOutput < 0){
        analogWrite(M1_Forward, 0);
        analogWrite(M1_Aft, -1*_leftOutput);
    }else if (_leftOutput == 0){
        analogWrite(M1_Forward, 0);
        analogWrite(M1_Aft, 0);
    }
    
    if (_rightOutput > 0){
        analogWrite(M2_Forward, _rightOutput);
        analogWrite(M2_Aft, 0);
    }else if (_rightOutput < 0){
        analogWrite(M2_Forward, 0);
        analogWrite(M2_Aft, -1*_rightOutput);
    }else if (_rightOutput == 0){
        analogWrite(M2_Forward, 0);
        analogWrite(M2_Aft, 0);
    }
}