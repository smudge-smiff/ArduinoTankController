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
    _leftOutput= mapToRange(processedLeftOutput, -1.0, 1.0, M2_Lower_Limit, M2_Upper_Limit);
    _rightOutput= mapToRange(processedRightOutput, -1.0, 1.0, M1_Lower_Limit, M1_Upper_Limit);
    //varDEBUG(processedLeftOutput);
    Serial.print(_leftOutput);
    Serial.print(" ");
    Serial.println(_rightOutput);
}
void Controller::motorSmoothing(){
    if (_leftOutputPrevious < M2_Mid_Point && _leftOutput > M2_Mid_Point){
        _leftOutput = M2_Mid_Point;
        DEBUG("LMU");
    }else if (_leftOutputPrevious > M2_Mid_Point && _leftOutput < M2_Mid_Point){
        _leftOutput = M2_Mid_Point;
        DEBUG("LML");
    }

    if (_rightOutputPrevious < M1_Mid_Point && _rightOutput > M1_Mid_Point){
        _rightOutput = M1_Mid_Point;
    }else if (_rightOutputPrevious > M1_Mid_Point && _rightOutput < M1_Mid_Point){
        _rightOutput = M1_Mid_Point;
    }
    _leftOutputPrevious = _leftOutput;
    _rightOutputPrevious = _rightOutput;
}
void Controller::motorOutput(){
    _leftMotor.writeMicroseconds(_leftOutput);
    _rightMotor.writeMicroseconds(_rightOutput);
}