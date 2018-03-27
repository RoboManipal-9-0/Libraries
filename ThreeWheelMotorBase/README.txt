################################################################################
  ThreeWheelMotorBase.cpp - Library code for controlling a three wheel bot
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra

  Testing phase status : PENDING with no deadline decided

################################################################################

This Library is built for motion of a three wheel omni drive

Instructions for users
- This library is build under the following assumptions
    - All angles are taken COUNTER CLOCKWISE
    - The triangular base is viewed from the TOP VIEW, in such an orientation that it appears as a delta
    - The NORTH of this delta is the zero degrees axis. Indexing of motors, angles, all measurements happen COUNTER CLOCKWISE to this axis.
      - Motor 1 (index 0) is directly on this axis, Motor 2 (index 1) is 120 degrees from Motor 1 (Counter clockeise), Motor 3 (index 2) is 240 degrees from Motor 1 (Counter clockwise).

############################## DOCUMENTATION ##############################

In order to use this library, you must have an object of class 'ThreeWheelMotorBase' (class description and definition is included in this library).
For example,
        ThreeWheelMotorBase motors;

This library includes the following functions (as of the latest build)

- void attachMagDirPins(int MAG_PINS[3],int DIR_PINS[3],boolean CCW_DIRS[3])
      This is to initialise the pins and tell the correct voltage levels.
      For example
        We have the Magnitude pins on pin number 9,10,11; Direction pins on pin number 4,5,6
        and the voltage levels to supply the individual motors so that they impart CCW angular momentum as HIGH,LOW,HIGH (this depends upon connections purely)
        Pass this function the following :
          int mag_pins[3] = {9,10,11};
          int dir_pins[3] = {4,5,6};
          boolean CCW_dirs[3] = {HIGH,LOW,HIGH};
          // Function call here :
          motors.attachMagDirPins(mag_pins,dir_pins,CCW_dirs);

- (1/2) - void setThreshold(float MAX_MAGS[3])
- (2/2) - void setThreshold(float MAX_value)
      This is used to cap the magnitude of motors (to prevent them from ever crossing a threshold).
      For example,
        We don't want motors 0,1 and 2 to exceed thresholds 200,250 and 225 respectively.
        This is done by :
          int MAX_MAGs[3] = {200,250,225};
          // Function call here :
          motors.setThreshold(MAX_MAGs);
        Alternatively, if we want to set the thresholds of all motors to just one value (say 300)
        This is done by :
          // Function call here :
          motors.setThreshold(300);

- void moveAtMagInDir(float magnitude, float angle)
      This is to actuate the motion of bot. Basucally, to move the bot at an angle (in degrees) and follow with a magnitude of velocity.
      For example
        We want the bot to move at an angle of 45 degrees and with magnitude 200, this function call is given by :
          // Function call here :
          motors.moveAtMagInDir(200,45);
        You can use any angle and magnitude
