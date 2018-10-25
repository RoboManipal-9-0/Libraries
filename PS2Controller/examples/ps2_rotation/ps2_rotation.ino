#include <PS2Controller.h>
#include <BotBase.h>
#include <D45Base.h>

D45Base robotBase;
PS2Controller myPS2(A11,A12);

int D45BASE_DIRs[] = {47, 53, 51, 49};
int D45BASE_PWMs[] = {8, 10, 9, 7};
bool D45BASE_REVs[] = {false, false, true, true};
#define ROTATION_SPEEDS 140

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
myPS2.InitializePS2Serial(115200);

robotBase.Initialize("FWS_1", &Serial2, 4);
myPS2.InitializeDebugger(&Serial,2);
robotBase.AssignPins(D45BASE_PWMs, D45BASE_DIRs, D45BASE_REVs);
Serial.println("Going into loop ... ");
robotBase.Move(0, 0);
}


float angle_degrees;
bool scale_factor=LOW;
int speeds;
void loop() {
  // put your main code here, to run repeatedly:
myPS2.ReadButtonStates();
if(myPS2.select_Bstate==HIGH)
{
  scale_factor=!scale_factor;
}
if(myPS2.left1_Bstate==HIGH)
{
  robotBase.Rotate(ROTATION_SPEEDS);
}
if(myPS2.right1_Bstate==HIGH)
{
  robotBase.Rotate(-ROTATION_SPEEDS);
}
myPS2.ReadPS2Values();
myPS2.AdjustCoordinates();
myPS2.CalcAngleSpeed();
angle_degrees=myPS2.angle*180/3.1416;
speeds= (scale_factor==HIGH)?(myPS2.speeds/2):myPS2.speeds;
robotBase.Move(speeds,angle_degrees);
}
