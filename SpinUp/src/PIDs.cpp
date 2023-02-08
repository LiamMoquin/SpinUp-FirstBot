#include "vex.h"
#include "PIDs.h"
using namespace std;

//i stands for "initial"
//m stands for "maintained"
//f stands for "final"

void mtrReset(){ //Resets motor value
  frontLeft.resetRotation();
  rearLeft.resetRotation();
  frontRight.resetRotation();
  rearRight.resetRotation();
}

float mtrAvg()//averages motor degrees
{
  return ((frontLeft.rotation(degrees) + frontRight.rotation(degrees) + rearLeft.rotation(degrees) + rearRight.rotation(degrees)) / 4);
  //returns motor average
}

float totalTargetDeg; //degrees to rotate over the whole motion
float lastError; //error in the last iteration
float error; //error in the current iteration
float akP = 1.6; //proportional tuning value
float akD = 0; //derivative tuning value

float drivePercTotal = 0;
float lastTargetVelocity = 0;

void driveStraighti(float dist/*target dist (in)*/, float vi = 0/*initial velocity*/, float vf = 100/*final velocity*/, float rUpDist = 0.2/*distance to ramp up over*/){
  mtrReset();
  
  error = 0; //sets error to 0
  lastError = 0; //sets lastError to 0
  
  totalTargetDeg = (dist / (2 * M_PI * (wheelDiameter / 2) / gearRatio) * 360);
  //Brain.Screen.print(totalTargetDeg);
  /*Target distance in degrees explanation:
  "dist" is the target in inches
  "(2 * M_PI * (wheelDiameter/2))"" is the calculation to find the circumference of the wheels
  "* 360" converts the distance and circumferance to degrees*/

  float targetDeg = (totalTargetDeg * rUpDist);//Sets target degrees for this specific instantiation
  /*Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(mtrAvg());
  Brain.Screen.setCursor(1, 10);
  Brain.Screen.print(targetDeg);*/

  while (mtrAvg() >= targetDeg)
  {
    error = (std::abs(frontLeft.rotation(degrees) + rearLeft.rotation(degrees)) - (std::abs(frontRight.rotation(degrees) + rearRight.rotation(degrees))));
    //error is how far from 0 the left motors - the right motors are
    Brain.Screen.setCursor(2, 1);
    //Brain.Screen.print(error);

    double accelCalc = (vf - vi) * (mtrAvg() / targetDeg) + vi;
    //how fast should the robot be moving?

    frontRight.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    frontLeft.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    rearRight.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    rearLeft.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    //sets velocity of motors to pid outputs
    
    frontLeft.spin(fwd);
    rearLeft.spin(fwd);
    frontRight.spin(fwd);
    rearRight.spin(fwd);
    //makes motors spin
    lastError = error;

    wait(25, msec);
  }
  drivePercTotal = drivePercTotal + rUpDist;
  lastTargetVelocity = vf;
}

void driveStraightc(float endDistPerc = 0.8)
{
  mtrReset();

  error = 0; //sets error to 0
  lastError = 0; //sets lastError to 0

  mtrReset();

  float targetDeg = (totalTargetDeg * (endDistPerc - drivePercTotal));//Sets target degrees for this specific instantiation

  while (mtrAvg() <= targetDeg)
  {
    error = (std::abs(frontLeft.rotation(degrees) + rearLeft.rotation(degrees)) - (std::abs(frontRight.rotation(degrees) + rearRight.rotation(degrees))));
    //error is how far from 0 the left motors - the right motors are

    frontLeft.setVelocity(((error * akP) + akD * (error - lastError)) - lastTargetVelocity, rpm);
    rearLeft.setVelocity(((error * akP) + akD * (error - lastError)) - lastTargetVelocity, rpm);
    frontRight.setVelocity(lastTargetVelocity - ((error * akP) + akD * (error - lastError)), rpm);
    rearRight.setVelocity(lastTargetVelocity - ((error * akP) + akD * (error - lastError)), rpm);
    //sets velocity of motors to pid outputs
    
    frontLeft.spin(fwd);
    rearLeft.spin(fwd);
    frontRight.spin(fwd);
    rearRight.spin(fwd);
    //makes motors spin
    lastError = error;
    wait(25, msec);
  }
  drivePercTotal = drivePercTotal + endDistPerc;
}

void driveStraightf(float vf, float endDistPerc)
{
  mtrReset();

  error = 0;
  lastError = 0;
  
  mtrReset();
  
  float targetDeg = totalTargetDeg * (endDistPerc - drivePercTotal);
  while(mtrAvg() <= targetDeg)
  {
    error = (std::abs(frontLeft.rotation(degrees) + rearLeft.rotation(degrees)) - (std::abs(frontRight.rotation(degrees) + rearRight.rotation(degrees))));
    
    double accelCalc = (vf = lastTargetVelocity) * (mtrAvg() / targetDeg) + lastTargetVelocity;

    frontLeft.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    rearLeft.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    frontRight.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    rearRight.setVelocity((accelCalc - ((error * akP ) + akD * (error - lastError))), rpm);

    frontLeft.spin(fwd);
    rearLeft.spin(fwd);
    frontRight.spin(fwd);
    rearRight.spin(fwd);

    lastError = error;

    wait(25, msec);
  }
  drivePercTotal = drivePercTotal + endDistPerc;
  lastTargetVelocity = vf;
}









//Turn PDs

float tkP = 1.6; //proportional tuning value
float tkD = 0; //derivative tuning value
float errorRange = 1; //acceptable error range

void turnPD(float targetHead, float vt)
{
  float error = targetHead - imu.heading();
  float lastError = 0;

  while (imu.heading() <= targetHead + errorRange)
  {
    float targetVel = (error * tkP + (error - lastError) * tkD + error + vt);
    frontLeft.setVelocity(-targetVel, percent);
    rearLeft.setVelocity(-targetVel, percent);
    frontRight.setVelocity(targetVel, percent);
    rearRight.setVelocity(targetVel, percent);

    frontLeft.spin(fwd);
    rearLeft.spin(fwd);
    frontRight.spin(fwd);
    rearRight.spin(fwd);

    lastError = error;
  }
}