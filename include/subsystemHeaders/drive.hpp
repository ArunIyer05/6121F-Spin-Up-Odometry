#include "main.h"


//HELPER FUNCTIONS
void setDrive(int left, int right);
void resetDriveEncoders();

double avgDriveEncoderValue();
double leftDriveEncoderValue();
double rightDrivbeEncoderValue();
void resetDriveEncoders();
void resetPIDVars(int left_units, int right_units);


//DRIVER CONTROL FUNCTIONS
void setDriveMotors();
void noTrap(double time, double dir);

//autonomous

void translate(int units, int voltage);
void translate(double units, double speed);
void straightTrap(double inches, double breakSpeed, int acceleration);
void turnTrap(double units, int breakRot, double dir, int accel);
