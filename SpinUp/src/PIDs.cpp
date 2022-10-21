#include "vex.h"
#include "PIDs.h"

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

void driveStraighti(float dist/*target dist (in)*/, float vi = 0/*initial velocity*/, float vf = 100/*final velocity*/, float rUpDist = 0.2/*distance to ramp up over*/){
  mtrReset();

  error = 0; //sets error to 0
  lastError = 0; //sets lastError to 0

  mtrReset();

  totalTargetDeg = (dist / (2 * M_PI * (2.75/2)) * 360) * 2;
  /*Target distance in degrees explanation:
  "dist" is the target in inches
  "(2 * M_PI * (2.75/2))"" is the calculation to find the circumference of the wheels
  "* 360" converts the distance and circumferance to degrees
  "* 2" is to double the degrees the motors need to spin
  We double the target degrees because the wheels are at a 45 degree angle and
  that halves distance traveled (they're all traveling diagonally so doubling accounts for that)*/

  float targetDeg = (totalTargetDeg * rUpDist);//Sets target degrees for this specific instantiation

  while (mtrAvg() <= targetDeg)
  {
    error = (abs(frontLeft.rotation(degrees) + rearLeft.rotation(degrees)) - (abs(frontRight.rotation(degrees) + rearRight.rotation(degrees))));
    //error is how far from 0 the left motors - the right motors are

    double accelCalc = (vf - vi) * (mtrAvg() / targetDeg) + vi;
    //how fast should the robot be moving?

    frontLeft.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    rearLeft.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    frontRight.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    rearRight.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    //sets velocity of motors to pid outputs
    
    frontLeft.spin(forward);
    rearLeft.spin(forward);
    frontRight.spin(forward);
    rearRight.setVelocity(forward);
    //makes motors spin
    lastError = error;
    wait(25, msec);
  }
}
