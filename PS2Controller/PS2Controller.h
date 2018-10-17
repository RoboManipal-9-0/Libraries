#ifndef PS2CONTROLLER
#define PS2CONTROLLER

//Modified Cytron PS2 Shield library
#include<CytronPS2.h>
// To use the PS2 on software serial pins
#include <SoftwareSerial.h>

//to use with Cytron PS2 Shield
class PS2Controller{
protected:

    //#################### PS2 SoftwareSerial Variables #########
    String serial_name;
    int rx_pin;
    int tx_pin;

    float RightX;
    float RightY;
    float left_x;
    float left_y;
    //######################PS2 BUTTON STATES#################
    bool start_Bstate;
    bool select_Bstate;

    bool triangle_Bstate;
    bool circle_Bstate;
    bool cross_Bstate;
    bool square_Bstate;

    // Creating an object of the Cytron_PS2Shield class
    CytronPS2 ps2;
    // ############################ Debugger #############################
    // Debugger output through serial
    int debuggerPriorityLevel;
    void DebuggerOutput(int Level, String output);
    HardwareSerial *ps2DebuggerSerial;

public:
  //Empty constructor
  PS2Controller();
  // COnstructor to initialise the software serial pins.
  PS2Controller(int rx_pin, int tx_pin);

  // The desired speed and angle values calculated from the PS2
  int speeds;
  float angle;

  //###################### DEBUGGER ############################
  // Initializing debugger serial parameters
  void InitializeDebugger(HardwareSerial *debugger_serial, int Level);
  // Setting the debugger priority, messages less than this level are not displayed
  void SetDebuggerPriorityToLevel(int minLevel);

  // #################### PS2 ###################################
  // Initialize PS2Serial baud rate
  void InitializePS2Serial(uint32_t baud_rate);
  // To read PS2 button values
  void ReadButtonStates(String button);
  //To obtain the analog values from the left side of the joystick
  void ReadPS2Values();
  //To calculate angle value and the speed from the analog input obtained from the PS2
  void CalcAngleSpeed();
  // To convert the coordinates from -128 to 128
  void AdjustCoordinates();

};

#endif
