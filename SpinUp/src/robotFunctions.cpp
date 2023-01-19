#include "vex.h"
#include "robotFunctions.h"

void delay(int milliseconds)
{
  vex::task::sleep(milliseconds);
}

void shoot()//activates piston to push disc into flywheel
{
  Piston.set(true);
  delay(100);
  Piston.set(false);

  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Shot Trigger");
}

bool endGame()
{
  if ((60 - Brain.timer(seconds) >= 10) && Controller2.ButtonDown.pressing()) return true;

  else return false;
}

void expand(bool armed = false)
{
  if (armed == true)
  {
    for (int i = 0; i<10; i++)
    {
      Expansion.set(true);
      wait(100,msec);
      Expansion.set(false);

      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("Expansion Trigger");
    }
  }
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