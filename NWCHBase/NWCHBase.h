/*
    NWCHBase.h - Library for N wheel concentric holonomic base made using omni wheels
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/
// Sanity check
#ifndef NWCHBASE_H
#define NWCHBASE_H

// Arduino main files
#include "Arduino.h"
#include "BotBase.h"

class NWCHBase : public BotBase {
protected:
    void Move_PWM_Angle(int PWM, float angle_radian, float w = 0);
};

#endif
