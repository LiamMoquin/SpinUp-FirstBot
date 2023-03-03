#include "vex.h"
#include "autonFunctions.h"
#include "robotFunctions.h"
#include "PIDs.h"

using namespace vex;

//shitty code section
void driveTime(float seconds, float speed)
{
  frontLeft.setVelocity(speed, percent);
  rearLeft.setVelocity(speed, percent);
  frontRight.setVelocity(speed, percent);
  rearRight.setVelocity(speed, percent);

  frontLeft.spin(forward);
  rearLeft.spin(forward);
  frontRight.spin(forward);
  rearRight.spin(forward);

  wait(seconds, sec);

  frontLeft.stop();
  rearLeft.stop();
  frontRight.stop();
  rearRight.stop();
}
void driveInches(float dist, float speed)
{
  frontLeft.setVelocity(speed, percent);
  rearLeft.setVelocity(speed, percent);
  frontRight.setVelocity(speed, percent);
  rearRight.setVelocity(speed, percent);

  frontLeft.spinFor(forward, dist/wheelDiameter*M_PI*360*gearRatio, degrees, false);
  rearLeft.spinFor(forward, dist/wheelDiameter*M_PI*360*gearRatio, degrees, false);
  frontRight.spinFor(forward, dist/wheelDiameter*M_PI*360*gearRatio, degrees, false);
  rearRight.spinFor(forward, dist/wheelDiameter*M_PI*360*gearRatio, degrees, false);
}


//end of shitty code (ish)


void allspin(void) //sets motors to spin at whatever velocity has been previously set
{
  frontLeft.spin(forward);
  rearLeft.spin(forward);
  frontRight.spin(forward);
  rearRight.spin(forward);
}

void allstop(void) //stops all motors
{
  frontLeft.stop();
  rearLeft.stop();
  frontRight.stop();
  rearRight.stop();
}

void visionStrafe(float speed /*speed to move at*/) //strafes to track an object with the vision sensor
{
  while(true)
  {
    float deadzone = .002; //sets deadzone (acceptable error range)

    Vision20.takeSnapshot(Vision20__SIG_1); //takes a snapshot of objects in signature (sig) 1
    //spin in a circle to the left
    while(Vision20.objects[0].exists == false) //while nothing is in the sensor fov
    {
      Vision20.takeSnapshot(Vision20__SIG_1);
      frontLeft.setVelocity(-speed,percent);
      rearLeft.setVelocity(-speed,percent);
      frontRight.setVelocity(speed,percent);
      rearRight.setVelocity(speed,percent);
      allspin();
    }
    
    while(Vision20.objects[0].exists) //while an object matching sig 1 exists
    {
      Vision20.takeSnapshot(Vision20__SIG_1);
      //strafe left
      while(Vision20.objects[0].centerX <= (157 - deadzone)) //while the object's center is to the left of the sensor center
      {
        Vision20.takeSnapshot(Vision20__SIG_1);
        //sets the velocity for the motors
        frontLeft.setVelocity(-speed,percent);
        rearLeft.setVelocity(speed,percent);
        frontRight.setVelocity(speed,percent);
        rearRight.setVelocity(-speed,percent);
      }
      //strafe right
      while(Vision20.objects[0].centerX >= (157 + deadzone)) //while the object's center is to the right of the sensor center
      {
        Vision20.takeSnapshot(Vision20__SIG_1);
        frontLeft.setVelocity(speed,percent);
        rearLeft.setVelocity(-speed,percent);
        frontRight.setVelocity(-speed,percent);
        rearRight.setVelocity(speed,percent);
      }
      //do nothing
      while((Vision20.objects[0].centerX <= (157 + deadzone)) && (Vision20.objects[0].centerX >= (157 - deadzone))) //while the object's center is in the sensor center
      {
        Vision20.takeSnapshot(Vision20__SIG_1);
        allstop();
      }
    }
  }
}

void trigMove(float distx, float disty, float vi, float vf, float rUpDist)
{
  float angleCalc = atan(distx/disty);
  float distCalc = sqrt(pow(distx,2) + pow(disty,2));

  turnPD(angleCalc);
  driveStraighti(distCalc, vi, vf, rUpDist);
  driveStraightc(1-rUpDist);
  driveStraightf(0, rUpDist);
}