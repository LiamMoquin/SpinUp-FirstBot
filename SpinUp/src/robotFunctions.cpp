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
  Roller.setVelocity(90, percent);
  Roller.spin(forward);
  /*int aHue = OpticalSensor.hue();
  printf("%i",aHue);
  while(aHue >= 50)
  {
    Roller.setVelocity(100, percent);
    Roller.spin(forward);
    aHue = OpticalSensor.hue();
  }
  while(aHue <= 50)
  {
    delay(50);
    Roller.stop();
    aHue = OpticalSensor.hue();
  }*/
}