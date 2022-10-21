#include "vex.h"
#include "robotFunctions.h"

void delay(int milliseconds)
{
  vex::task::sleep(milliseconds);
}

void shoot()//activates piston to push disc into flywheel
{
  Piston.set(false);
  delay(100);
  Piston.set(true);
}

void tempCheck()//warns if temperature is too high
{
  Brain.Screen.setCursor(10,3);
  Brain.Screen.setPenColor(red);
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
  if(FlywheelFront.temperature(celsius) >= 45)
  {
    Brain.Screen.setCursor(11,1);
    Brain.Screen.print("FLYWHEEL FRONT OVERHEAT!!!");
  }
  if(FlywheelRear.temperature(celsius) >= 45)
  {
    Brain.Screen.setCursor(12,1);
    Brain.Screen.print("FLYWHEEL REAR OVERHEAT!!!");
  }
}

void rollerScore(bool redTeam)
{
  if(redTeam)
  {
  }
}