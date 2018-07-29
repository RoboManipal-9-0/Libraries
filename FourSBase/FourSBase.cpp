#include "FourSBase.h"

// ###################### Derived class : BotBase #######################
FourSBase::FourSBase() {
    // 4 wheel bot
    this->setNumberOfWheelsTo(4);
}
// Add motor driver pins
void FourSBase::AddPins(int *PWM_PINs, int *DIR_PINs, bool *reversePINs) {
    // Call the function of super class and assign PWM, DIR pins
    this->AddMotorDriverPins(PWM_PINs, DIR_PINs);
    // Assign reverse directions
    this->reverseDIRs = reversePINs;
    // Debugger output
    String message = "Wheel Reverse DIRs : ";
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        message.concat(reversePINs[i]);
        message.concat(" ");
    }
    this->DebuggerOutput(2, message);
}
// Motion code (angle in radians)
void FourSBase::Move_PWM_Angle(int PWM, float angle) {
    // PWM vector created from directions
    int PWM_vector[4] = {
        PWM * sin(angle),
        -1 * PWM * cos(angle),
        -1 * PWM * sin(angle),
        PWM * cos(angle)
    };
    int PWM_abs_vector[4];
    int DIR_vector[4] = {false, false, false, false};
    // Get the DIR_values vector from PWM_vector and get PWM_values
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
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
    this->PWM_values = PWM_abs_vector;
    this->DIR_values = DIR_vector;
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        Serial.print(PWM_vector[i]);
        Serial.print(":");
        Serial.print(this->PWM_values[i]);
        Serial.print(":");
        Serial.print(this->DIR_values[i]);
        Serial.print(" ");
    }
    Serial.println();
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        this->MoveMotor(i);
    }
}
