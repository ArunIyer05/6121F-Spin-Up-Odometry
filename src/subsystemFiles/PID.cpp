#include "main.h"

//u(t) = Kp e(t) +Ki integral(e(t)dt) + Kp de/dt

//e(t) = error
//Kp = proportional gain
//de = change in error
//dt = change in time
//Ki = constant

double kP = 0.0;
double kI = 0.0;
double kD = 0.0;
double turnkP = 0.0;
double turnkI = 0.0;
double turnkD = 0.0;

int desiredValue = 200;
int turnValue = 0;

int error;
int prevError = 0;
int derivative;
int totalError;

int turnError;
int turnPrevError = 0;
int turnDerivative = 0;
int turnTotalError = 0;

bool enabledPID = true;

int PID() {
  while (enabledPID) {
    int leftMotorPosition = leftDriveFront.get_position();
  }
  return 1;
}
