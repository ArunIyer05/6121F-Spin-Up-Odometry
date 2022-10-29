#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */



void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	pros::lcd::initialize();
	//pros::lcd::set_text(1, "6121F Starting");

	pros::lcd::register_btn1_cb(on_center_button);
	//setPneumatics(true);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//odomTest();
	//setDrive(-60,60);
	//setDrive(10,10);
	// tareEncoders();
	// while(true){
	// 	pros::lcd::clear_line(1);
	// 	pros::lcd::set_text(1, "theta: " + std::to_string(theta() *(180/3.141592653589793238)));
	// 	pros::lcd::set_text(2, "posX: " + std::to_string(localX()));
	// 	pros::lcd::set_text(3, "posZ: " + std::to_string(localZ()));
	// 	pros::delay(10);
	// }
	// setDrive(-60,60);
	// while(true){
	// 	deltaTheta();
	// 	pros::delay(10);
	// }
}

void odomTest(){
	tareEncoders();

}



void rightSide(){ //gets win point on right side
	raiseClaw(127, 250); //raises claw
	straightTrap(7.8, 10,1800); //goes forward to alliance mogo

	setPneumatics(false);
	//openClamp(-60, 1300.0); //deploys ring

	straightTrap(-3, 10,1800); //reverses slightly

	raiseClaw(-127, 200); //lowers claw
	straightTrap(5.0, 40,1800); //forward slightly

	//openClamp(127, 600.0); //clamps on alliance mogo
	setPneumatics(true);
	straightTrap(-12.0, 10,1800); //reverse back to cross line
}

	void leftSide(){
		setPneumatics(false);
		straightTrap(20, 30, 300); //drive to left side mogo
		//openClamp(127, 500.0); //get left mogo
		pros::delay(500);
		setPneumatics(true);

			//raiseClaw(127, 50); //picks up mogo slightly
		straightTrap(-20,30,500);
		raiseClaw(127, 200);
		turnTrap(6, 40, -1, 500);
		straightTrap(6, 30, 500);
		liftMogo(127, 1250);
		straightTrap(-12, 30, 500);
		liftMogo(-127, 1250);
		runIntake(-127, 2000);
		liftMogo(127, 800);

	}

// void leftSide(){ //scores win point then gets left mogo
// 	raiseClaw(127, 200);
// 	straightTrap(8.1, 10,1800);
// 		//openClamp(-127, 200.0);
// 	setPneumatics(false);
// 	straightTrap(-9, 10,1800);
// 	//raiseClaw(-127, 500);
//
//
// 	turnTrap(9.7, 20, 1, 1800);
// 	liftMogo(127, 1200.0);
// 	straightTrap(-31, 30,1800);
// 	liftMogo(-127, 1000);
//
// 	straightTrap(28.0,25,1800);
// }
// //void leftSide2(){
// 	turnTrap(9.6, 20, 1, 1800);
// 	liftMogo(127, 1400);
// 	straightTrap(-31, 30,1800);
// 	liftMogo(-127, 1000);
//
// 	straightTrap(28.0,35,1800);
//
// 	turnTrap(-8, 20, 1, 1800);
// 	raiseClaw(127, 800);
// 	straightTrap(4, 30,1800);
// 	setPneumatics(false);
// //	openClamp(-127, 900);
//}
void rush(){
	setPneumatics(false);
	straightTrap(17, 30, 000); //drive to left side mogo
	//openClamp(127, 500.0); //get left mogo
	pros::delay(500);
	setPneumatics(true);
	pros::delay(500);
	//raiseClaw(127, 50); //picks up mogo slightly
	straightTrap(-24,30,500);


}
void rushMid(){
	straightTrap(36, 30, 500); //drive to left side mogo
	setPneumatics(true);
		//openClamp(127, 500.0); //get left mogo
	raiseClaw(127, 400); //picks up mogo slightly
	straightTrap(-30,30,500);
}

// void leftDualRush(){
// 	openClamp(-127, 600.0); //open clamp
// 	straightTrap(29, 30, 500); //drive to left side mogo
// 	openClamp(127, 500.0); //get left mogo
// 	raiseClaw(127, 400); //picks up mogo slightly
// 	straightTrap(-24,30,500); //backs up into home zone
// 	//raiseClaw(127,400); //raise claw
// 	turnTrap(10,20,-1); // turn
// 	openClamp(-127,600); //release mogo
// 	//straightTrap(-3,30,700); //back up slightly
// 	raiseClaw(127,400); //
// 	turnTrap(12, 20, 1); //turn counterclockwise to aim at center mogo
// 	raiseClaw(-127,500);
// 	noTrap(1300,-1); //go forward towards center mogo
// 	openClamp(127,400.0); //close clamp on center mogo
// 	noTrap(1300,1); //reverse back into home zone
// }
void leftDualRush(){
	//openClamp(-127, 600.0); //open clamp
	straightTrap(29, 30, 500); //drive to left side mogo
	setPneumatics(true);
		//openClamp(127, 500.0); //get left mogo
	raiseClaw(127, 100); //picks up mogo slightly
	straightTrap(-24,30,500);
	raiseClaw(127, 300);
	turnTrap(9.0,50,-1, 0);

	straightTrap(2, 30, 200);
		//openClamp(-127, 300);
	setPneumatics(false);
	liftMogo(127, 1250);
	straightTrap(-35, 30, 500);
	pros::delay(1000);
	liftMogo(-127,900);
	straightTrap(29, 30, 500);
	// openClamp(-127, 600);
	// straightTrap(-6,30,200);
	// turnTrap(9.9,50,1, 500);
	// raiseClaw(-127, 600);
	// straightTrap(33,40,500);
	// openClamp(127,800);
	// straightTrap(-25, 30, 0);

}
void autonSkills(){
	straightTrap(16, 30, 1800);
	pros::delay(500);
	turnTrap(6.8, 30, -1, 500);
	straightTrap(5, 30, 1800);
	liftMogo(127, 1250);
	straightTrap(-13, 30, 1800);
	liftMogo(-127, 950);
	runIntake(-127, 2000);
	straightTrap(11, 30, 1800);




	pros::delay(1000);
	turnTrap(7, 30, 1, 500);
	straightTrap(22, 30, 1800);
	pros::delay(1000);
	setPneumatics(true);
	pros::delay(1000);
	raiseClaw(127, 270);
	turnTrap(5, 50, -1, 500);
	straightTrap(25, 30, 1800);
	pros::delay(1000);
	raiseClaw(127, 900);
	turnTrap(3.5,50,1,200);
	straightTrap(18, 30, 1800);
	//raiseClaw(-127, 400);
	pros::delay(750);
	raiseClaw(-127, 400);
	setPneumatics(false);
	pros::delay(750);


	raiseClaw(127, 300);
	straightTrap(-12, 30, 1800);
	pros::delay(750);
	liftMogo(127, 750);
	straightTrap(8, 30, 1800);
	liftMogo(-127, 1200);
	//pros::delay(1000);
	turnTrap(11.5, 30, -1, 500);
	pros::delay(750);
	raiseClaw(-127, 800);

	straightTrap(15, 30, 1800);
	pros::delay(750);
	setPneumatics(true);
	pros::delay(750);
	raiseClaw(127, 200);
	pros::delay(750);
	turnTrap(11, 40, -1, 500); //very important make sure it works
	pros::delay(750);
	raiseClaw(127, 800);
	pros::delay(750);
	straightTrap(20, 30, 1800);
	raiseClaw(-127, 300);
	setPneumatics(false);
	raiseClaw(-127, 300);
	pros::delay(750);
	raiseClaw(127, 300);
	pros::delay(750);
	//109 consistent
	straightTrap(-15, 30, 1800);
	turnTrap(3, 40, 1, 500);
	straightTrap(-50, 30,1800);


	//129 experimental
	// straightTrap(-7, 30, 1800);
	// turnTrap(6.4, 40, -1, 500);
	// raiseClaw(-127, 800);
	// pros::delay(750);
	// straightTrap(38, 30, 1800);
	// pros::delay(750);
	// setPneumatics(true);
	// turnTrap(4, 40, 1, 500);
	//straightTrap(-100, 30, 1800);




}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	tareEncoders();
	while(true){
		double prevL = getLeftEncoder();
		double prevR = getRightEncoder();
		double prevS = getBackEncoder();
		pros::delay(10);
		double curL = getLeftEncoder();
		double curR = getRightEncoder();
		double curS = getBackEncoder();
		odometryBaseCode(prevL, prevR, prevS, curL, curR, curS);
		setDriveMotors();
		// setIntakeMotors();
		// //toggleIntake();
		// setMogoMotors();
		// setClawMotors();
		// setClampMotors();
		// pneumaticsOp();
	}
}
