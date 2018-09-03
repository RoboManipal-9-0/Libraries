// Include headers
#include "PIDController.h"

// ::::::::::::: Constructors ::::::::::::::::::
PIDController::PIDController() {
    // Nothing here
}

PIDController::PIDController(String name, double Kp, double Ki, double Kd) {
    // Name of the controller
    this->name = name;
    // Assign Kp, Ki and Kd
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    
}
