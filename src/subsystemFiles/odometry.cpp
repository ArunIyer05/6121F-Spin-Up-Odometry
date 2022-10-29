#include "main.h"

//pros::ADIDigitalIn back('C');
double sL = 3.5/2; //distance from tracking center
double sR = 3.5/2;
double sS = 0/2;
// double sL = 3.5/2;
// double sR = 5/2;
// double sS = 11/2;
double circumference = 3.141592653589793238 * 2.75;
double degreesToRadConversion = 3.141592653589793238/180;
double radToDegreesConversion = 1/degreesToRadConversion;

void tareEncoders(){
  left.set_position(0);
  right.set_position(0);
  back.set_position(0);
  left.reverse();
  back.reverse();
}
double getLeftEncoder(){
  return left.get_position();
}
double getRightEncoder(){
  return right.get_position();
}
double getBackEncoder(){
  return back.get_position();
}



double theta(){

  double curLeftPos = left.get_position()/(double) 100; //left encoder is reversed
  double curRightPos = right.get_position()/(double) 100; //positions of the encoders
  double deltaL = circumference*curLeftPos/(double) 360; //total distance traveled by left tracking wheel
  double deltaR = circumference*curRightPos/(double) 360; //total distance traveled by right tracking wheel
  double theta = (deltaL- deltaR)/(sL + sR); //calculation for angle theta
  return theta;
}





// double localX(){
//   double curBackPos = back.get_position()/(double) 100;
//   double deltaS = circumference*curBackPos/(double) 360;
//   double localX;
//   if(theta() == 0)
//     localX = deltaS;
//   else{
//     localX = 2*sin(theta()/2)*((deltaS/theta()) + sS);
//   }
//   return localX;
// }
// double localZ(){
//   double curLeftPos = left.get_position()/(double) 100; //left encoder is reversed
//   double curRightPos = right.get_position()/(double) 100; //positions of the encoders]
//   double deltaL = circumference*curLeftPos/(double) 360; //total distance traveled by left tracking wheel
//   double deltaR = circumference*curRightPos/(double) 360; //total distance traveled by right tracking wheel
//   double localZ;
//   if(theta() == 0)
//     localZ = deltaR;
//   else{
//     localZ = 2*sin(theta()/2)*((deltaR/theta()) + sR);
//   }
//   return localZ;
// }
 double localX(double deltaL, double deltaR, double deltaS, double deltaTheta){ //helper function
  double locX;
  if(deltaTheta == 0)
    locX = deltaS;
  else
    locX = 2*sin(deltaTheta/2)*((deltaS/deltaTheta) +sS);
  return locX;
}


double localZ(double deltaL, double deltaR, double deltaS, double deltaTheta){ //helper function
 double locZ;
 if(deltaTheta == 0)
   locZ = deltaR;
 else
   locZ = 2*sin(deltaTheta/2)*((deltaR/deltaTheta) +sR);
 return locZ;
}



double deltaTheta;
double averageOrientation;
double theta0, theta1;
double locX, locZ;
double polarR, localOrientation;
double xcord, zcord;

double xCoord(double deltaL, double deltaR, double deltaS, double deltaTheta, double averageOrientation){
  if(localX(deltaL, deltaR, deltaS, deltaTheta) == 0){
    polarR = localZ(deltaL, deltaR, deltaS, deltaTheta);
    localOrientation = 3.141592653589793238/2;
  }else{
    polarR = sqrt(localX(deltaL, deltaR, deltaS, deltaTheta)*localX(deltaL, deltaR, deltaS, deltaTheta)+
    localZ(deltaL, deltaR, deltaS, deltaTheta)*localZ(deltaL, deltaR, deltaS, deltaTheta));
    if(localX(deltaL, deltaR, deltaS, deltaTheta) < 0){
      polarR = -polarR;
    }
    localOrientation = atan(localZ(deltaL, deltaR, deltaS, deltaTheta)/localX(deltaL, deltaR, deltaS, deltaTheta));
  }

  localOrientation -= averageOrientation;
  xcord += polarR*cos(localOrientation);
  return xcord;
}
double zCoord(double deltaL, double deltaR, double deltaS, double deltaTheta, double averageOrientation){
  if(localX(deltaL, deltaR, deltaS, deltaTheta) == 0){
    polarR = localZ(deltaL, deltaR, deltaS, deltaTheta);
    localOrientation = 3.141592653589793238/2;
  }else{
    polarR = sqrt(localX(deltaL, deltaR, deltaS, deltaTheta)*localX(deltaL, deltaR, deltaS, deltaTheta)+
    localZ(deltaL, deltaR, deltaS, deltaTheta)*localZ(deltaL, deltaR, deltaS, deltaTheta));
    if(localX(deltaL, deltaR, deltaS, deltaTheta) < 0){
      polarR = -polarR;
    }
    localOrientation = atan(localZ(deltaL, deltaR, deltaS, deltaTheta)/localX(deltaL, deltaR, deltaS, deltaTheta));
  }

  localOrientation -= averageOrientation;
  zcord += polarR*sin(localOrientation);
  return zcord;
}
double dist;
void odometryBaseCode(double prevL, double prevR, double prevS, double curL, double curR, double curS){
  //calculate change in encoders: 1, 2, 3


  double deltaL = (circumference*curL/(double) 36000) - (circumference*prevL/(double) 36000);
  double deltaR = (circumference*curR/(double) 36000) - (circumference*prevR/(double) 36000);
  double deltaS = (circumference*curS/(double) 36000) - (circumference*prevS/(double) 36000);
  double LVal = (circumference*curL/(double) 36000);
  double RVal = (circumference*curR/(double) 36000);


  //Step 4: calc change since reset
  // double deltaLr = circumference*curL/(double) 36000; //total distance traveled by left tracking wheel
  // double deltaRr = circumference*curR/(double) 36000; //total distance traveled by right tracking wheel
  // double deltaSr = circumference*curS/(double) 36000; //total distance traveled by back tracking wheel
  //
  // double deltaPrevLr = circumference*prevL/(double) 36000; //total distance traveled by left tracking wheel
  // double deltaPrevRr = circumference*prevR/(double) 36000; //total distance traveled by right tracking wheel
  // double deltaPrevSr = circumference*prevS/(double) 36000; //total distance traveled by back tracking wheel

  deltaTheta+=(deltaL-deltaR)/(sL+sR);
  averageOrientation = theta1 + (deltaTheta/2);
  theta1 += deltaTheta;
  dist += fabs((deltaL - (sL*deltaTheta)));



  pros::lcd::set_text(1, "theta: " + std::to_string(theta1 *(180/3.141592653589793238)));
  pros::lcd::set_text(2, "posX: " + std::to_string(xCoord(deltaL, deltaR, deltaS, deltaTheta, averageOrientation)));
  pros::lcd::set_text(3, "posZ: " + std::to_string(zCoord(deltaL, deltaR, deltaS, deltaTheta, averageOrientation)));
  pros::lcd::set_text(4, "distTraveled: " + std::to_string(dist));

  deltaTheta = 0;
}

void odometryAuto(double prevL, double prevR, double prevS, double curL, double curR, double curS, double targetX, double targetZ){
  //calculate change in encoders: 1, 2, 3


  double deltaL = (circumference*curL/(double) 36000) - (circumference*prevL/(double) 36000);
  double deltaR = (circumference*curR/(double) 36000) - (circumference*prevR/(double) 36000);
  double deltaS = (circumference*curS/(double) 36000) - (circumference*prevS/(double) 36000);

  //Step 4: calc change since reset
  // double deltaLr = circumference*curL/(double) 36000; //total distance traveled by left tracking wheel
  // double deltaRr = circumference*curR/(double) 36000; //total distance traveled by right tracking wheel
  // double deltaSr = circumference*curS/(double) 36000; //total distance traveled by back tracking wheel
  //
  // double deltaPrevLr = circumference*prevL/(double) 36000; //total distance traveled by left tracking wheel
  // double deltaPrevRr = circumference*prevR/(double) 36000; //total distance traveled by right tracking wheel
  // double deltaPrevSr = circumference*prevS/(double) 36000; //total distance traveled by back tracking wheel

  deltaTheta+=(deltaL-deltaR)/(sL+sR);
  averageOrientation = theta1 + (deltaTheta/2);
  theta1 += deltaTheta;
  double xPos = xCoord(deltaL, deltaR, deltaS, deltaTheta, averageOrientation);
  double zPos = zCoord(deltaL, deltaR, deltaS, deltaTheta, averageOrientation);

  double desiredTheta = atan(targetZ/targetX);

  while(theta1 > desiredTheta+5 || theta1 < desiredTheta - 5){
    if(theta1 > desiredTheta + 5)
      setDrive(-40,40);
    else
      setDrive(40,-40);
  }
  while(xPos < targetX -2 && zPos < targetZ - 2)
    setDrive(50,50);



  // pros::lcd::set_text(1, "theta: " + std::to_string(theta1 *(180/3.141592653589793238)));
  // pros::lcd::set_text(2, "posX: " + std::to_string(xCoord(deltaL, deltaR, deltaS, deltaTheta, averageOrientation)));
  // pros::lcd::set_text(3, "posZ: " + std::to_string(zCoord(deltaL, deltaR, deltaS, deltaTheta, averageOrientation)));

  deltaTheta = 0;
}







// void odometry(double prevL, double prevR, double prevS, double prevTheta, double curL, double curR, double curS, double curTheta){
//
//
//   double deltaFrameL = curL - prevL;
//   double deltaFrameR = curR - prevR;
//   double deltaFrameS = curS - prevS;
//
//   double encoderL = (-1)*left.get_position()/(double) 100;
//   double encoderR = right.get_position()/(double) 100;
//   double encoderS = back.get_position()/(double) 100;
//
//   double deltaL = circumference*encoderL/(double) 360; //total distance traveled by left tracking wheel
//   double deltaR = circumference*encoderR/(double) 360; //total distance traveled by right tracking wheel
//   double deltaS = circumference*encoderS/(double) 360; //total distance traveled by back tracking wheel
//
//   double deltaTheta = curTheta - prevTheta;
//   double averageOrientation = curTheta +(deltaTheta/2);
//   double polarR;
//   double localOrientation;
//   double posX, posZ;
//
//   double localX;
//     if(curTheta == 0)
//       localX = deltaS;
//     else
//       localX = 2*sin(curTheta/2)*((deltaS/deltaTheta + sS));
//
//   double localZ;
//     if(curTheta == 0)
//       localZ = deltaR;
//     else
//       localZ = 2*sin(curTheta/2)*((deltaR/deltaTheta) + sR);
//
//
//     if(localX == 0){
//       polarR = localZ;
//       localOrientation = 3.141592653589793238/2;
//     }
//     else{
//       polarR = sqrt(localX*localX + localZ*localZ);
//       if(localX < 0)
//         polarR = -polarR;
//       localOrientation = tan(localZ/localX);
//     }
//
//     localOrientation -= averageOrientation;
//     posX += polarR*cos(localOrientation);
//     posZ += polarR*sin(localOrientation);
//
//   pros::lcd::set_text(1, "theta: " + std::to_string(curTheta *(180/3.141592653589793238)));
//   pros::lcd::set_text(2, "posX: " + std::to_string(posX));
//   pros::lcd::set_text(3, "posZ: " + std::to_string(posZ));
//
// }



void turnOnSpot(double correctAngle, int speed){

}





void driveStraight(double dist, int speed){
  //
  // double Kp = 9;
  // double Ki = 9;
  // double Kd = 9;
  // double target = dist;
  // double sensValue = (left.get_position()/(double) 100)*degreesToRadConversion*2.75;
}
