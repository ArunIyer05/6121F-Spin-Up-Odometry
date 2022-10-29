#include "main.h"

//calibration for gyro: change when we get access to both
// positive is left, negative is right
//pros::ADIGyro gyro('B', 0.91);

//CONSTANTS AND VARIABLES

//robot measurements
const static double WHEEL_DIAMETER = 4.125;
const static double GEAR_RATIO = 36.0 / 60.0;
const static double TICKS_PER_INCH = 900.0 / (M_PI * WHEEL_DIAMETER * GEAR_RATIO); //900 ticks per revolution

const static double CHASSIS_WIDTH = 12.0; //length from wheel to wheel on opposite side
const static double TICKS_PER_DEGREE = (2.5 * CHASSIS_WIDTH) / (WHEEL_DIAMETER * GEAR_RATIO); //only for turning not arc


//field measurement constants
const static double GOAL_RUSH = 67.5;

static double leftTarget = 0.0;
double leftPos = 0.0;
double leftError = leftTarget - leftPos;
std::vector<double> leftPrevErrors(2, leftError);
double leftDerivative = 0.0;
double leftIntegral = 0.0;
double leftPower = 0.0;




static double rightTarget = 0.0;
double rightPos = 0.0;
double rightError = rightTarget - rightPos;
std::vector<double> rightPrevErrors(2, rightError);
double rightDerivative = 0.0;
double rightIntegral = 0.0;
double rightPower = 0.0;

const int BRAKE_TIME = 100; //just trying out a new brake time - original was 50


double avgDriveEncoderValue() {
  return (fabs(leftDriveFront.get_position()) + fabs(leftDriveBack.get_position()) + fabs(rightDriveFront.get_position())+ fabs(rightDriveBack.get_position())) / 4;
}

double leftDriveEncoderValue()
{
  // return (fabs(driveLeftFront.get_position()) +
  //         fabs(driveLeftBack.get_position())) / 2;
  return (leftDriveFront.get_position() +
          leftDriveBack.get_position()) / 2;
}

double rightDriveEncoderValue()
{
  // return (fabs(driveRightFront.get_position()) +
  //         fabs(driveRightBack.get_position())) / 2;
  return (rightDriveFront.get_position() +
          rightDriveBack.get_position()) / 2;
}



//HELPER FUNCTIONS

void resetDriveEncoders() {
  leftDriveBack.tare_position();
  leftDriveFront.tare_position();
  rightDriveBack.tare_position();
  rightDriveFront.tare_position();
}
void resetPIDVars(int left_units, int right_units) {
  resetDriveEncoders();

  leftTarget = left_units;
  leftPos = leftDriveEncoderValue();
  leftError = leftTarget - leftPos;
  leftPrevErrors.assign(2, leftError);
  leftDerivative = 0;
  //leftIntegral = accumulate(leftPrevErrors.begin(), leftPrevErrors.end(), -2.0*leftError);
  leftPower = 0;


  rightTarget = right_units;
  rightPos = rightDriveEncoderValue();
  rightError = rightTarget - rightPos;
  rightPrevErrors.assign(2, rightError);
  rightDerivative = 0;
  //rightIntegral = accumulate(rightPrevErrors.begin(), rightPrevErrors.end(), -2.0*rightError);
  rightPower = 0;
}




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


//AUTONOMOUS CONTROL FUNCTIONS
void translate(double units, double speed){
  int count = 0;
  int total = 0;
  leftDriveBack.tare_position();
  leftDriveFront.tare_position();
  rightDriveBack.tare_position();
  rightDriveFront.tare_position();

  double sign;
  if(speed < 0){
    sign = -1;
    speed *= -1;
  }
  else if(speed > 0)
    sign = 1;

  int slope = 3;
  double changeArea = (speed)*(speed/slope);
  double stagnation = (units - changeArea*2)/speed;

  while(total < units){
    setDrive(count*sign,count*sign);

    if(count < speed && total < units/2)
      count+= slope;

    if(count < speed && total > units/2 && count > 0)
        count -= slope;
    if(count >= speed){
      int counter = 0;
      if(counter < stagnation)
        counter++;
      else
        count-= slope;

    }
    total += count;
    pros::delay(10);
  }
  //setDrive(0,0);
  // while(true)
  //   setDrive(100,100);
}
// //void translate(int units, int voltage) {
//   //define direction
//   int direction = abs(units) / units;
//   //reset motor encoders and gyro
//   resetDriveEncoders();
//   gyro.reset();
//   //drive forwards until units are reached
//   while(averageDriveEncoderValue() < abs(units)) {
//     //gyro may correct by too much, may need to add scaling coeffs later
//     setDrive(voltage * direction + gyro.get_value(), voltage * direction - gyro.get_value());
//     pros::delay(10);
//   }
//   //brake
//   setDrive(-10 * direction, -10 * direction);
//   pros::delay(50);
//   //set drive back to neutral
//   setDrive(0, 0);
// }

void noTrap(double time,double dir){
  int count = 0;
  while(count < time/10){
    count++;
      setDrive(dir*127,dir*127);
      //mogolift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


    pros::delay(10);

  }
  setDrive(0,0);
}

void straightTrap(double inches, double breakSpeed, int acceleration) {

  pros::lcd::set_text(1, "Trap Drive");

  double direction = fabs(inches) / inches; //either 1 or -1

  //inches /= 4*3.141592653589793238; //1 rotation of the wheel is this many inches

  resetPIDVars(inches*TICKS_PER_INCH, inches*TICKS_PER_INCH);

  int INTL_VEL = 20;
  int MAX_VEL = 127;
  int TARGET_BUFFER = acceleration; //num of units (each side) for acceleration and deceleration (the higher the value the slower the acceleration)




  while (fabs(avgDriveEncoderValue()) < TARGET_BUFFER && fabs(avgDriveEncoderValue()) <= fabs(rightTarget + leftTarget)/4) { //change from 4 to 2
    int cv = -(INTL_VEL + (int)(fabs(avgDriveEncoderValue())*(MAX_VEL - INTL_VEL)/TARGET_BUFFER));

    setDrive(cv * direction, cv * direction);
    pros::delay(10);
  }

  while (fabs(avgDriveEncoderValue()) <= fabs(rightTarget + leftTarget)/2 - TARGET_BUFFER) {
    double cv = -MAX_VEL;
    setDrive(cv * direction, cv * direction);
    pros::delay(10);
  }

  while (fabs(avgDriveEncoderValue()) < fabs(rightTarget + leftTarget)/2) {
    double e = fabs(avgDriveEncoderValue()) - fabs(rightTarget + leftTarget)/2;
    double cv = (int)((e / TARGET_BUFFER) * (MAX_VEL - INTL_VEL));
    setDrive(cv * direction, cv * direction);
    pros::delay(10);


    if(fabs(cv) <= breakSpeed){ //30 works for now
      setDrive(0,0);
      break;
    }





  pros::delay(BRAKE_TIME);
  setDrive(0, 0);
  }
}

void turnTrap(double units, int breakRot, double dir, int accel) {

  //Dir 1 = clockwise, Dir -1 = counterclockwise

  pros::lcd::set_text(1, "Turn Drive");

  double direction = fabs(units) / units; //either 1 or -1
  resetPIDVars(units*TICKS_PER_INCH, units*TICKS_PER_INCH);

  int INTL_VEL = 20;
  int MAX_VEL = 127;
  int TARGET_BUFFER = accel; //num of units (each side) for acceleration and deceleration (the higher the value the slower the acceleration)

  int time = 5000;
  int count = 0;


  while (fabs(avgDriveEncoderValue()) < TARGET_BUFFER && fabs(avgDriveEncoderValue()) <= fabs(rightTarget + leftTarget)/4) {
    int cv = -(INTL_VEL + (int)(fabs(avgDriveEncoderValue())*(MAX_VEL - INTL_VEL)/TARGET_BUFFER));

    setDrive(-cv*direction*dir, cv * direction*dir);
    pros::delay(10);
  }

  while (fabs(avgDriveEncoderValue()) <= fabs(rightTarget + leftTarget)/2 - TARGET_BUFFER) {
    int cv = -MAX_VEL;
    setDrive(-cv*direction*dir, cv * direction*dir);
    pros::delay(10);
    count++;
  }

  while (fabs(avgDriveEncoderValue()) < fabs(rightTarget + leftTarget)/2) {
    double e = fabs(avgDriveEncoderValue()) - fabs(rightTarget + leftTarget)/2;
    double cv = (int)((e / TARGET_BUFFER) * (MAX_VEL - INTL_VEL));
    setDrive(-cv*direction*dir, cv * direction*dir);

    pros::delay(10);


    if(fabs(cv) <= breakRot){ //30 works for now
      setDrive(0,0);
      break;
    }





  pros::delay(BRAKE_TIME);
  setDrive(0, 0);
  }


}
