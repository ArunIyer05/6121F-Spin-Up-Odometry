#include "main.h"


void setClaw(int power){
  claw = power;
  claw2 = power;
}

void setClawMotors(){
  int clawPower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
  if(abs(clawPower) < 127){

    claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    claw2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    claw.move_velocity(0);
    claw2.move_velocity(0);

  }
  else{
  setClaw(clawPower);

  }
}

void raiseClaw(int power, double time){
  int count = 0;
  while(count < time/10){
    count++;
    setClaw(power);
    pros::delay(10);
  }
  claw.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  claw.move_velocity(0);
  claw2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  claw2.move_velocity(0);
  setClaw(0);
  //count = 0;
}
