/*
 * Test for RazorIMU_9DOF
 * 
 * Tested by: Avneesh Mishra
 * Testing device: Arduino Mega (Atmega 2560)
 * IMU connected to serial 1 (Serial1) and debugger connected to Serial
 * 
 * Test status: Test successfully completed (40ms delay in worst case scenario)
 */
#include <RazorIMU_9DOF.h>

// Declare an object of RazorIMU_9DOF type
RazorIMU_9DOF IMU;
void setup() {
  // Initialize the Serials
  Serial1.begin(57600);
  Serial.begin(115200);
  // Attach the debugger serial
  IMU.debugger.Initialize("IMU_9DOF", &Serial);
  // Attach the IMU Serial
  IMU.AttachIMUSerial(&Serial1);
  // Set the IMU reference values (in the beginning)
  IMU.ResetReference();  
}

void loop() {
  // Update data from IMU
  IMU.UpdateData();
  // Get the YAW value
  float yaw = IMU.GetYaw();         // Continuous YAW value (0 to 360)
  float yaw_raw = IMU.GetRaw_YAW(); // Raw YAW value (-180 to 180)
  float yaw_rel = IMU.GetRel_YAW(); // Relative to the previous positioning
  // Print this message on the serial
  String msg = "Yaw [Continuous, Raw, Relative]: ";
  msg.concat(yaw);
  msg.concat(" ");
  msg.concat(yaw_raw);
  msg.concat(" ");
  msg.concat(yaw_rel);
  Serial.println(msg);
  // Same for pitch
  float pitch = IMU.GetPitch();         // Continuous PITCH value (0 to 360)
  float pitch_raw = IMU.GetRaw_PITCH(); // Raw PITCH value (-180 to 180)
  float pitch_rel = IMU.GetRel_PITCH(); // Relative to the previous positioning
  // Print this message on the serial
  msg = "Pitch [Continuous, Raw, Relative]: ";
  msg.concat(pitch);
  msg.concat(" ");
  msg.concat(pitch_raw);
  msg.concat(" ");
  msg.concat(pitch_rel);
  Serial.println(msg);
  // Same for roll
  float roll = IMU.GetRoll();         // Continuous PITCH value (0 to 360)
  float roll_raw = IMU.GetRaw_ROLL(); // Raw PITCH value (-180 to 180)
  float roll_rel = IMU.GetRel_ROLL(); // Relative to the previous positioning
  // Print this message on the serial
  msg = "Roll [Continuous, Raw, Relative]: ";
  msg.concat(roll);
  msg.concat(" ");
  msg.concat(roll_raw);
  msg.concat(" ");
  msg.concat(roll_rel);
  Serial.println(msg);
}
