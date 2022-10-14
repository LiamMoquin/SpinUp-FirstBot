#include "vex.h"
#include "PIDs.h"

//i stands for "initial"
//m stands for "maintained"
//f stands for "final"

void mtrReset(){
  frontLeft.resetRotation();
  rearLeft.resetRotation();
  frontRight.resetRotation();
  rearRight.resetRotation();
}

double mtrAvg()
{
  return ((frontLeft.rotation(degrees) + frontRight.rotation(degrees) + rearLeft.rotation(degrees) + rearRight.rotation(degrees)) / 4);
}

double totalTargetDeg; //degrees to rotate over the whole motion
double lastError; //error in the last iteration
double error; //error in the current iteration
double akP = 1.6; //proportional tuning value
double akD = 0; //derivative tuning value

void driveStraighti(float dist, float vi = 0, float vf = 100, float rUpDist = 0.2){
  mtrReset();

  error = 0; //sets error to 0
  lastError = 0; //sets lastError to 0

  mtrReset();

  totalTargetDeg = (dist / (2 * M_PI * (2.75/2)) * 360) * 2;

  double targetDeg = (totalTargetDeg * rUpDist);

  while (mtrAvg() <= targetDeg)
  {
    error = (abs(frontLeft.rotation(degrees) + rearLeft.rotation(degrees)) - (abs(frontRight.rotation(degrees) + rearRight.rotation(degrees))));
    double accelCalc = (vf - vi) * (mtrAvg() / targetDeg) + vi;

    frontLeft.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    rearRight.setVelocity((((error * akP) + akD * (error - lastError)) + accelCalc), rpm);
    frontRight.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    rearRight.setVelocity((accelCalc - ((error * akP) + akD * (error - lastError))), rpm);
    
    lastError = error;
    wait(25, msec);
  }
}
