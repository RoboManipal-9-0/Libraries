/*
  FourSBase.h - Library to deal with Four wheel holonomic drive base
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Check for the flag
#ifndef FOURSBASE_H
#define FOURSBASE_H

// Include main files
#include "BotBase.h"

// Four wheels attached in an S configuration
class FourSBase : public BotBase {
protected:
    // To give provision to reverse connect the direction pins
    bool *reverseDIRs;
    void Move_PWM_Angle(int PWM, float angle_radians);
public:
    FourSBase();
    void AddPins(int *PWM_pins, int *DIR_PINs, bool *reverseDIRs);
};

#endif
