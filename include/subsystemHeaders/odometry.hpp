#include "main.h"

void odometry();

//helper functions - getters and setters
void tareEncoders();
double getLeftEncoder();
double getRightEncoder();
double getBackEncoder();

double theta();
double localX();
double localZ();
void turnOnSpot(double correctAngle, int speed);
void driveStraight(double dist, int speed);
double localX(double deltaL, double deltaR, double deltaS, double deltaTheta);
double localZ(double deltaL, double deltaR, double deltaS, double deltaTheta);
void odometryBaseCode(double prevL, double prevR, double prevS,
   double curL, double curR, double curS);
void odometryAuto(double prevL, double prevR, double prevS,
      double curL, double curR, double curS, double targetX, double targetZ);
