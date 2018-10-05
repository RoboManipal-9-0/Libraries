/*
    NWCHBase.h - Library for N wheel concentric holonomic base made using omni wheels
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/
// Including the library
#include "NWCHBase.h"

// ##################### Constructors #####################
NWCHBase::NWCHBase() {
    // Empty constructor
}
NWCHBase::NWCHBase(int num_wheels) {
    // Initialize number of wheels
    this->InitializeWheels(num_wheels);
}
NWCHBase::NWCHBase(int num_wheels, int *angle_deg) {
    // Initialize number of wheels and their angles (in degrees)
    this->InitializeWheels(num_wheels, angle_deg);
}
// ############## Initializer functions #####################
void NWCHBase::InitializeWheels(int num_wheels) {
    // Set the number of wheels
    this->setNumberOfWheelsTo(num_wheels);
}
void NWCHBase::InitializeWheels(int *angles_deg) {
    // Convert the angles in degrees to radians and save it into angles
    // Debugger message (Level: INFO)
    // Initializing angle configuration: %ang1_deg%(%ang1_rad%) %ang2_deg%(%ang2_rad%) ... %angN_deg%(%angN_rad%)
    // Examples: 
    // Initializing angle configuration: 45(0.785398) 135(2.356194) 225(3.926990) 315(5.497787)
    // Initializing angle configuration: 90(1.570796) 210(3.665191) 330(5.759586)
    String msg = "Initializing angle configuration: ";
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i ++) {
        this->angles[i] = angles_deg[i] * DEG_TO_RAD;    // Convert angles to radians and assign them
        msg.concat(angles_deg[i]);
        msg.concat("(");
        msg.concat(this->angles[i]);
        msg.concat(") ");
    }
    this->debugger.print(INFO, msg);
}
void NWCHBase::InitializeWheels(int num_wheels, int *angles_deg) {
    // Call the above two functions 
    this->InitializeWheels(num_wheels);
    this->InitializeWheels(angles_deg);
}
// ####################### Main motion code ##########################
void NWCHBase::Move_PWM_Angle(int PWM, float angle, float w) {
    /*
     * Motion of the N Wheel Concentric Holonomic Base
     * @param PWM:   Velocity magnitude to move 
     * @param angle: Angle of motion of the bot
     * @param w:     Angular velocity of the bot with respect to center of the bot
     */
    // Properties (for the actuation)
    float Vx = PWM * sin(angle);      // X component of velocity
    float Vy = PWM * cos(angle);      // Y component of velocity
    float *vector;                    // Actuation vector
    // Debugger message (Level: DEBUG)
    // Wheel motion vector: %val1% %val2% %val3% ... %valN%
    // Example:
    // Wheel motion vector: -10 100 24 -98
    // Wheel motion vector: 76 54 -76 -54
    String msg = "Wheel motion vector: ";
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        // Vi = Vx Sin(Qi) + Vy Cos(Qi) + w
        vector[i] = Vx * sin(this->angles[i]) + Vy * cos(this->angles[i]) + w;
        // Debugger message
        msg.concat(vector[i]);    
        msg.concat(" ");
    }
    this->debugger.print(DEBUG, msg);
    // Convert to PWM and DIR values
    this->VectorTo_PWM_DIR(vector);
}