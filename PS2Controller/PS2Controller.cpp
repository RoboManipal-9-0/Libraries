#include <PS2Controller.h>

//Constructor to initialise the RX and TX Pins for Software Serial
PS2Controller::PS2Controller(int rx_pin, int tx_pin)
{
  ps2.Initialize(rx_pin,tx_pin);
}

//###################### DEBUGGER ############################
// Initializing debugger serial parameters
void PS2Controller::InitializeDebugger(HardwareSerial *debugger_serial, int Level)
{
  // Debugger serial of bot
  this->ps2DebuggerSerial = debugger_serial;
  // Priority level of the debugger
  this->debuggerPriorityLevel = Level;
}
// Initialises baud rate for PS2 Serial
// Note that the baud rate should be  same as the jumper connection with PS2 shield
void PS2Controller::InitializePS2Serial(uint32_t baud_rate)
{
  ps2.begin(baud_rate);
}
// Setting the debugger priority, messages less than this level are not displayed
void PS2Controller::SetDebuggerPriorityToLevel(int minLevel)
{
  this->debuggerPriorityLevel = minLevel;
}
//######################## PS2 ###################################
// To read PS2 button values
void PS2Controller::ReadButtonStates()
{
  this->left1_Bstate=this->ps2.readButton(PS2_LEFT_1);
  this->right1_Bstate=this->ps2.readButton(PS2_RIGHT_1);
  this->select_Bstate=this->ps2.readButton(PS2_SELECT);
  this->cross_Bstate=this->ps2.readButton(PS2_CROSS);
  //this->DebuggerOutput(1, message);
}

//To obtain the analog values from the left side of the joystick
void PS2Controller::ReadPS2Values()
{
  // Read analog values from the right side of the joystick
  this->left_x = 255 - this->ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS);
  this->left_y = this->ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);

  /*String message=" PS2 VALUES: ";
  message.concat(" X coordinates : ");
  message.concat(this->left_x);
  message.concat("     Y coordinates : ");
  message.concat(this->left_y);
  this->DebuggerOutput(1,message); */
}

//Calculate the value of the angle in radians
void PS2Controller::CalcAngleSpeed(int scaling_factor)
{
  // CAlculate the angle of desired motion
  float temp=(float)this->left_y/ this->left_x;
  this->angle=atan2(this->left_x,this->left_y);
  // To keep angle range 2pi radians
  if(this->angle<0)
  {
    this->angle=3.14+(3.14+this->angle);
  }
  // Maps the circular coordinate space into a sqaure
  this->speeds=pow(pow(this->left_x,2)+pow(this->left_y,2),0.5);
  this->speeds=scaling_factor*(this->speeds>127?127:this->speeds);


  String message="";
  message.concat("Angle: ");
  message.concat(this->angle);
  message.concat("      Speed : ");
  message.concat(speeds);
  this->DebuggerOutput(2,message);

}

// To convert the coordinates from -128 to 128
void PS2Controller::AdjustCoordinates(){
  // Values mapped from 0 - 255 to -127- 128 to emulate Cartesian coordinates
  this->left_x=-(this->left_x-127);
  this->left_y=-(this->left_y-127);

  /*String message="";
  message.concat("COORDINATES : ");
  message.concat(" X= ");
  message.concat(this->left_x);
  message.concat(" Y= ");
  message.concat(this->left_y);
  this->DebuggerOutput(2,message); */
}

// Debugger output function
void PS2Controller::DebuggerOutput(int level, String output) {
    // If the message priority is less, then no need to display
    if (this->debuggerPriorityLevel > level) {
        return;
    }
    // Print the message on serial monitor in fashion
    // $:L%level%: %output%
    this->ps2DebuggerSerial->print("$:L");
    this->ps2DebuggerSerial->print(level);
    this->ps2DebuggerSerial->print(": ");
    this->ps2DebuggerSerial->print(output);         // Main message
    this->ps2DebuggerSerial->println("");
}
