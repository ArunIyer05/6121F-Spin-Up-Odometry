#include "main.h"

//calibration for gyro: change when we get access to both
// positive is left, negative is right
//pros::ADIGyro gyro('B', 0.91);

//CONSTANTS AND VARIABLES

//robot measurements
//DRIVER CONTROL METHODS
void setDrive(int left, int right){
  leftDriveFront = left;
  leftDriveBack = left;
  rightDriveFront = right;
  rightDriveBack = right;
}



void setDriveMotors(){
  int leftJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightJoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  if(abs(leftJoystick) < 10)
    leftJoystick = 0;
  if(abs(rightJoystick) < 10)
      rightJoystick = 0;
  setDrive(leftJoystick, rightJoystick);
}
