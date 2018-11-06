#include <PS2Controller.h>

//Constructor to initialise the RX and TX Pins for Software Serial
PS2Controller::PS2Controller(int rx_pin, int tx_pin)
{
  ps2.Initialize(rx_pin,tx_pin);
  // PS2 Serial attached
  this->debugger.print("PS2 Serial attached", INFO);
  debugger.AttachSerial(&Serial);
}


// Initialises baud rate for PS2 Serial
// Note that the baud rate should be  same as the jumper connection with PS2 shield
void PS2Controller::InitializePS2Serial(uint32_t baud_rate)
{
  ps2.begin(baud_rate);
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

  // Debugger message (Level: DEBUG)
  // X: %X_COORDINATE%  Y:%Y_COORDINATE%
  // For example: X: 0  Y: 127
  String msg="X: ";
  msg.concat(this->left_x);
  msg.concat("   Y: ");
  msg.concat(this->left_y);
  this->debugger.print(msg,DEBUG); 
}

//Calculate the value of the angle in radians
void PS2Controller::CalcAngleSpeed(float scaling_factor)
{
  // CAlculate the angle of desired motion
  float temp=(float)this->left_y/ this->left_x;
  this->angle=atan2(this->left_x,this->left_y);
  // To keep angle range 2pi radians
  if(this->angle<0)
  {
    this->angle=3.14+(3.14+this->angle);
  }
  // The scaling factor is present to modify the maximum permissible speed for the bot
  this->speeds=scaling_factor* (pow(pow(this->left_x,2)+pow(this->left_y,2),0.5));


  String message="Angle: ";
  message.concat(this->angle);
  message.concat("      Speed : ");
  message.concat(speeds);
  this->debugger.print(message,DEBUG);

}

// To convert the coordinates from -128 to 128
void PS2Controller::AdjustCoordinates(){
  // Values mapped from 0 - 255 to -127- 128 to emulate Cartesian coordinates
  //Also the values are mapped from -127 to 127 to ensure a square which will later be used in the mapping
  this->left_x=-(this->left_x-127);
  if(this->left_x==-128)
    {
      this->left_x=-127;
    }
  this->left_y=-(this->left_y-127);
  if(this->left_y==-128){
    this->left_y=-127;
  }
   
  float temp;
  
// SIMPLE STRETCHING
// The following equations map the sqaure formed to a circle . Refer to the README for documentation
  if(pow(this->left_x,2)>=pow(this->left_y,2))
  {
    temp=pow(this->left_x,3)/(sqrt(pow(this->left_x,2)+pow(this->left_y,2))*abs(this->left_x));
    this->left_y=(this->left_y*pow(this->left_x,2))/(sqrt(pow(this->left_x,2)+pow(this->left_y,2))*abs(this->left_x));
    this->left_x=temp;
  }

  else 
  {
    temp=(this->left_x*pow(this->left_y,2))/(sqrt(pow(this->left_x,2)+pow(this->left_y,2))*abs(this->left_y));
    this->left_y=pow(this->left_y,3)/(sqrt(pow(this->left_x,2)+pow(this->left_y,2))*abs(this->left_y));
    this->left_x=temp;
    
  }

}
