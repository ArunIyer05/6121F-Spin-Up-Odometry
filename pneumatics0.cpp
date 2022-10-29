#include "main.h"


pros::ADIDigitalOut clampClaw('D');

bool isMogoClamped = false; //false is out, true is active clamp
bool mogoButtPress = false;


void setPneumatics(bool state){
    isMogoClamped = state;
    if(isMogoClamped) //true = clamped
      clampClaw.set_value(HIGH);
    else //false = not clamped
      clampClaw.set_value(LOW);

}

void pneumaticsOp(){
    if(controller.get_digital(DIGITAL_RIGHT) && !mogoButtPress){
        mogoButtPress = true;
      clampClaw.set_value(LOW);
    }

    else if(controller.get_digital(DIGITAL_LEFT) && !mogoButtPress){
      mogoButtPress = true;
        clampClaw.set_value(HIGH);
    }
    else
      mogoButtPress = false;
}
