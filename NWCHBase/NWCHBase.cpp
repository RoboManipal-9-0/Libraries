/*
    NWCHBase.h - Library for N wheel concentric holonomic base made using omni wheels
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/
// Including the library
#include "NWCHBase.h"

// Constructors
NWCHBase::NWCHBase() {
    // Empty constructor
}
NWCHBase::NWCHBase(int num_wheels) {
    
}

// ############## Initializer functions #####################
void NWCHBase::InitializeWheels(int num_wheels) {
    // Set the number of wheels
    this->setNumberOfWheelsTo(num_wheels);
}
void NWCHBase::InitializeWheels(int *angles_deg) {
    String msg = "Initializing angle configuration to ";
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i ++) {
        this->angles[i] = angles_deg[i] * DEG_TO_RAD;    // Convert angles to radians and assign them
    }
}

void NWCHBase::Move_PWM_Angle(int PWM, float angle, float w) {
    // TODO: Implement code for motion of NWCHBase 
}