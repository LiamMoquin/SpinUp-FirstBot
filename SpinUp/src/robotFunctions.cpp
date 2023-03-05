#include "vex.h"
#include "robotFunctions.h"

void delay(int milliseconds)
{
  vex::task::sleep(milliseconds);
}

//int shotCount = 0;
//int scoreCount = 0;
void shoot()//activates piston to push disc into flywheel
{
  Piston.set(true);
  wait(100,msec);
  Piston.set(false);
  
  //shotCount += 1;
}
/*void scoreAdd()
{
  scoreCount += 1;
}*/

bool endGame()
{
  if ((60 - Brain.timer(seconds) >= 10) && Controller2.ButtonDown.pressing()) return true;

  else return false;
}
void expand(bool armed = false)
{
  if (armed == true)
  {
    Expansion.set(true);
    Expansion2.set(true);

    Controller2.Screen.setCursor(3, 1);
    Controller2.Screen.print("Expansion Triggered");
    /*for (int i = 0; i<10; i++)
    {
      Expansion.set(true);
      wait(100,msec);
      Expansion.set(false);

      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("Expansion Trigger");
    }*/
  }
}

void tempCheck()//warns if temperature is too high
{
  //Brain.Screen.setCursor(10,3);
  //Brain.Screen.setPenColor(red);
  
  Controller2.Screen.setCursor(2,1);
  Controller2.Screen.print("MTR OVRHEAT: " );
  if(frontLeft.temperature(celsius) >= 45)
  {
    Brain.Screen.print("LEFT FRONT OVERHEAT!!!");
  }
  if(rearLeft.temperature(celsius) >= 45)
  {
    Brain.Screen.print("LEFT REAR OVERHEAT!!!");
  }
  if(frontRight.temperature(celsius) >= 45)
  {
    Brain.Screen.print("RIGHT FRONT OVERHEAT!!!");
  }
  if(rearRight.temperature(celsius) >= 45)
  {
    Brain.Screen.print("RIGHT FRONT OVERHEAT!!!");
  }
  if(Flywheel.temperature(celsius) >= 45)
  {
    Brain.Screen.setCursor(11,1);
    Brain.Screen.print("FLYWHEEL OVERHEAT!!!");
  }
  if(Roller.temperature(celsius) >= 45)
  {
    Brain.Screen.setCursor(12,1);
    Brain.Screen.print("ROLLER REAR OVERHEAT!!!");
  }
}

void rollerScore()
{
  Roller.setVelocity(30, percent);
  Roller.spin(forward);
  while(OpticalSensor.color() == red)
  {
    Roller.spin(forward);
  }
  while(OpticalSensor.color() == blue)
  {
    wait(50, msec);
    Roller.stop();
  }
}

int targetVel;

void setFly(int target){
  targetVel = target;
}

int flywheelP()
{
  float fkP = 2.4; //2.4 is a good value
  //-184,190

  float error = targetVel - Flywheel.velocity(rpm)*6;
  float velReq = ((targetVel + (error * fkP)) / 36) * 120;
  float offRPM = 0;
  float overRPM = 0;
  float underRPM = 0;
  printf("Target Velocity: %i\n", targetVel);
  while(true)
  {
    Brain.Screen.clearScreen();
    error = targetVel - Flywheel.velocity(rpm)*6;
    velReq = ((targetVel + (error * fkP)) / 36) * 120;
    //quick math checking velReq math
    //((3600 + (0)) / 36) * 12 = 100 * 12 = 1200
    //((3000 + (0)) / 36) * 12 = 100 * 12 = 1000
    //((3000 + (1000 * 0.2)) / 36) * 12 = ((3000 + 200) / 36) * 12 = (3200 / 36) * 12 = (88.88) * 12
    //printf("Velocity Request: %f Error: %f RPM: %f\n", velReq, error, Flywheel.velocity(rpm)*6);
    //printf("RPM: %f   OFF RPM: %f\n", Flywheel.velocity(rpm)*6, offRPM);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(error);
    Flywheel.spin(fwd, velReq, voltageUnits::mV);
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(Flywheel.velocity(rpm)*6);

    if((Flywheel.velocity(rpm) * 6) - targetVel > overRPM)
    {
      overRPM = (Flywheel.velocity(rpm) * 6) - targetVel;
    }
    if(((Flywheel.velocity(rpm) * 6) - targetVel < underRPM) && overRPM >= 1)
    {
      underRPM = (Flywheel.velocity(rpm) * 6) - targetVel;
    }
    offRPM = (Flywheel.velocity(rpm) * 6) - targetVel;
    printf("RPM: %f   UNDER RPM: %f   OVER RPM: %f\n", Flywheel.velocity(rpm)*6, underRPM, overRPM);

    wait(20,msec);
  }
  return 0;
}
