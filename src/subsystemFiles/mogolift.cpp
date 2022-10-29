#include "main.h"


void setMogo(int power){
  mogolift = power;
}

void setMogoMotors(){
  int mogoPower = 127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
  if(abs(mogoPower) < 90){

    mogolift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    mogolift.move_velocity(0);
  }
  else{
  setMogo(mogoPower);
  }


}

void liftMogo(int power, double time){
  int count = 0;
  while(count < time/10){
    count++;
      setMogo(power);
      mogolift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);


    pros::delay(10);

  }

  mogolift.move_velocity(0);
}
