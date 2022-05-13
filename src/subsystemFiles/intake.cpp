#include "main.h"
//VARIABLES
  bool activeIn = false;
  bool activeOut = false;
  bool toggled = false;
void setIntake(int power){
  intake = power;
}

void setIntakeMotors(){
  int intakePower =127*(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
  setIntake(intakePower);
}

void runIntake(int speed, double time){
  int count = 0;
  while(count < time/10){
    count++;
    setIntake(speed);
    pros::delay(10);
  }
  setIntake(0);
  //count = 0;
}

void toggleIntake(){
  if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && activeIn == false && toggled == false){ //intake off and L1 pressed to turn on
    activeIn = true;
    activeOut = false;
    toggled = true;
  }

  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && activeIn == true && toggled == true){ //intake on and L1 pressed to turn off
    activeIn = false;
    activeOut = false;
    toggled = false;
  }

  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && activeOut == true && toggled == true){ //intake on and L2 pressed to turn off
      activeOut = false;
      activeIn = false;
      toggled = false;
  }

  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && activeIn == false && toggled == false){ //intake off and L2 pressed to turn on
    activeOut = true;
    activeIn = false;
    toggled = true;
  }

  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && activeOut == true){ //intake on and L1 pressed to switch direction
      activeOut = false;
      activeIn = true;
      toggled = true;
    }
  else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && activeIn == true){ //intake on and L2 pressed to switch direction
      activeIn = false;
      activeOut = true;
      toggled = true;
    }




  if(activeIn == true && toggled == true)
    setIntake(127);
  else if(activeOut == true && toggled ==true)
    setIntake(-127);
  else if(toggled == false)
    setIntake(0);

}
