/*
  FourSBase.cpp - Library to deal with Four wheel holonomic drive base
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Shashank Goyal
*/

#include "FourSBase.h"

// ###################### Derived class : BotBase #######################
FourSBase::FourSBase() {
    // 4 wheel bot
    this->setNumberOfWheelsTo(4);
}
// Motion code (angle in radians)
void FourSBase::Move_PWM_Angle(int PWM, float angle,float w) {
    // PWM vector created from directions
    int PWM_vector[4] = {
        w + PWM * sin(angle),
        w + -1 * PWM * cos(angle),
        w + -1 * PWM * sin(angle),
        w + PWM * cos(angle)
    };
    int PWM_abs_vector[4];
    int DIR_vector[4] = {false, false, false, false};
    // Debugger message (Level: DEBUG)
    // Calculated wheel vectors : [ %val1% %val2% %val3% %val4% ]
    // For example
    // Calculated wheel vectors : [ 100 0 -100 0 ]
    String debuggerMessage = "Calculated wheel vectors : [ ";
    // Get the DIR_values vector from PWM_vector and get PWM_values
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        debuggerMessage.concat(PWM_vector[i]);
        debuggerMessage.concat(" ");
        if (PWM_vector[i] >= 0) {
            DIR_vector[i] = HIGH;
        } else {
            DIR_vector[i] = LOW;
        }
        if (this->reverseDIRs[i] == true) {
            DIR_vector[i] = !DIR_vector[i];
        }
        PWM_abs_vector[i] = abs(PWM_vector[i]);
    }
    debuggerMessage.concat("]");
    this->debugger.print(debuggerMessage, DEBUG);
    // PWM and direction assignment
    this->VectorTo_PWM_DIR(PWM_vector);
}
