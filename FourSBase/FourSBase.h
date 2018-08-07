#ifndef FOURSBASE
#define FOURSBASE

#include "BotBase.h"

// Four wheels attached in an S configuration
class FourSBase : public BotBase {
protected:
    // To give provision to reverse connect the direction pins
    bool *reverseDIRs;
    void Move_PWM_Angle(int PWM, float angle_radians);
public:
    FourSBase();
    void AddPins(int *PWM_pins, int *DIR_PINs, bool *reversePINs);
};

#endif
