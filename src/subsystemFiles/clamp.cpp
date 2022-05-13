#include "main.h"


void setClamp(int power){
  clamp = power;
}

void setClampMotors(){
  int clampPower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT));
  if(abs(clampPower) < 60){

    clamp.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    clamp.move_velocity(0);
  }
  else{
  setClamp(clampPower);
  }
}


void openClamp(int power, double time){
  int count = 0;
  while(count < time/10){
    count++;
    setClamp(power);
    pros::delay(10);
  }
  setClamp(0);
}
