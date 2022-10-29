#include "main.h"


//MOTORS

extern pros::Motor leftDriveFront;
extern pros::Motor leftDriveBack;
extern pros::Motor rightDriveFront;
extern pros::Motor rightDriveBack;
extern pros::Motor intake;
extern pros::Motor mogolift;
extern pros::Motor claw;
extern pros::Motor clamp;
extern pros::Motor claw2;
extern pros::Rotation left;
extern pros::Rotation right;
extern pros::Rotation back;

//CONTROLLER
extern pros::Controller controller;

extern pros::ADIGyro gyro;

#define leftTracking 'A'
#define rightTracking 'B'
#define backTracking 'C'

#define clampPneumatics 'D'
