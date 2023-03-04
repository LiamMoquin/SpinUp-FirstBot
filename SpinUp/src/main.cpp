/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// frontLeft            motor         5               
// rearLeft             motor         2               
// frontRight           motor         3               
// rearRight            motor         4               
// Controller1          controller                    
// Vision20             vision        20              
// Expander19           triport       19              
// Piston               digital_out   A               
// Flywheel             motor_group   17, 18          
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "autonFunctions.h"
#include "robotFunctions.h"
#include "autonSelector.h"
#include "PIDs.h"
#include "ButtonClass.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int autonSwitch = 3;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Controller2.Screen.clearScreen();
  OpticalSensor.setLightPower(200);
  /*imu.calibrate();
  while(imu.isCalibrating())
  {
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("Calibrating");
  }
  wait(2, sec);*/
  Brain.Screen.print("Complete");
  Brain.Screen.clearScreen();
  imu.setHeading(0, degrees);

  lcdButton Rightside(375,100,100,50,"Right", "#FF2525");
  lcdButton Leftside(125,100,100,50,"Left", "#FF2525");
  lcdButton ExpansionButton(250,50,100,50,"Expansion", "#FF2525");
  lcdButton PIDTest(250,200,100,50,"PIDTest", "#FF2525");
  Brain.Screen.setCursor(1, 1);

  while(true)
  {
    if(Leftside.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Left Selected");
      autonSwitch = 0;
      break;
    }

    if(Rightside.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Right Selected");
      autonSwitch = 1;
      break;
    }

    if(ExpansionButton.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Expansion Selected");
      autonSwitch = 2;
      break;
    }
    
    if(PIDTest.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("PID Test Selected");
      autonSwitch = 3;
      break;
    }
    if(Controller1.ButtonLeft.pressing())
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("PID Test Selected");
      autonSwitch = 3;
      break;
    }
  }

  /*while(1 != !1)
  {
    if(Leftside.pressing())
    {
      Brain.Screen.print("Left has been selected");
    }
  }*/

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void rollerSpin()
{
  Roller.setVelocity(30, percent);
  Roller.spin(reverse);
}
void rollerStop()
{
  Roller.stop();
}

void autonomous(void) {
  Brain.Screen.clearScreen();
  task FlywheelT = task(flywheelP);

  //left side auton
  if(autonSwitch == 0)
  {
    Flywheel.spin(fwd, 12000*.5, voltageUnits::mV);
    driveTime(.2, 100);
    rollerSpin();
    wait(500, msec);
    rollerStop();
    driveTime(.1, -50);

    frontLeft.spin(forward, 50, percent);
    rearLeft.spin(forward,50,percent);
    frontRight.spin(reverse, 50, percent);
    rearRight.spin(reverse, 50, percent);
    wait(425,msec);
    frontRight.stop();
    rearRight.stop();
    frontLeft.stop();
    rearLeft.stop();

    driveTime(1, -75);
    frontLeft.spin(fwd, 50, percent);
    rearLeft.spin(fwd, 50, percent);
    wait(425, msec);
    frontLeft.stop();
    rearLeft.stop();
    wait(500, msec);
    shoot();
    wait(1000, msec);
    shoot();

    /*
    frontLeft.spin(reverse, 50, percent);
    rearLeft.spin(reverse,50,percent);
    frontRight.spin(forward, 50, percent);
    rearRight.spin(forward, 50, percent);
    wait(425,msec);
    frontRight.stop();
    rearRight.stop();
    frontLeft.stop();
    rearLeft.stop();*/
  }

  //left side auton
  /*rollerSpin();
  driveTime(1, 50);
  wait(.2, sec);
  rollerStop();*/
  

  

  /*driveTime(1, 50);
  rollerSpin();
  wait(.75, sec);
  rollerStop();*/

  /*while (imu.heading() >= 225)
  {
    frontLeft.spin(reverse, 30, percent);
    rearLeft.spin(reverse, 30, percent);
    frontRight.spin(fwd, 30, percent);
    rearRight.spin(fwd, 30, percent);
  }*/

  //right side auton good
  if(autonSwitch == 1)
  {
    Flywheel.spin(fwd, 12000*.8, voltageUnits::mV);
    wait(4, sec);
    shoot();
    wait(500, msec);
    shoot();
  }

  //EXPANSION CODE
  if(autonSwitch == 2)
  {
    Flywheel.spin(fwd, 12000*.5, voltageUnits::mV);
    driveTime(.2, 100);
    rollerSpin();
    wait(500, msec);
    rollerStop();
    driveTime(.1, -50);

    frontLeft.spin(forward, 50, percent);
    rearLeft.spin(forward,50,percent);
    frontRight.spin(reverse, 50, percent);
    rearRight.spin(reverse, 50, percent);
    wait(425,msec);
    frontRight.stop();
    rearRight.stop();
    frontLeft.stop();
    rearLeft.stop();

    driveTime(1, -75);
    frontLeft.spin(fwd, 50, percent);
    rearLeft.spin(fwd, 50, percent);
    wait(425, msec);
    frontLeft.stop();
    rearLeft.stop();
    wait(500, msec);
    shoot();
    wait(1000, msec);
    shoot();
    wait(1000,msec);
    frontLeft.spin(reverse, 50, percent);
    rearLeft.spin(reverse, 50, percent);
    wait(750, msec);
    frontLeft.stop();
    rearLeft.stop();
    expand(true);
  }

  if(autonSwitch == 3)//pidTest
  {
    setFly(3600);

    /*imu.setHeading(180, degrees);
    frontLeft.setStopping(brake);
    rearLeft.setStopping(brake);
    frontRight.setStopping(brake);
    rearRight.setStopping(brake);
    
    Intake.spin(reverse, 12000, voltageUnits::mV);
    driveTime(.2, 100);
    rollerSpin();
    wait(500, msec);
    rollerStop();
    driveTime(.1, -50);
    turnPD(40);

    driveTime(2.2, 50);

    turnPD(90+55);
    wait(1, sec);
    shoot();
    wait(3, sec);
    shoot();
    wait(1,sec);
    shoot();*/

  }

  //driveStraighti(24, 10, 100, 0.2);
  //driveStraightc(0.8);
  //driveStraightf(0, 1);
  //trigMove(35, 30, 0, 70, .2);
  //visionStrafe(45);
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int flywheelState = 3600;

void flywheelSlowA()
{
  flywheelState = 0;
}
void flywheelSlowB()
{
  flywheelState = 3600 * .8;
}
void flywheelSlowY()
{
  flywheelState = 3600;
}

void usercontrol(void) {

  // User control code here, inside the loop

  Intake.spin(fwd, 12000, voltageUnits::mV);

  Brain.resetTimer();
  Controller2.Screen.clearScreen();
  Brain.Screen.clearScreen();
  Controller2.Screen.setCursor(1,1);
  Controller2.Screen.print("Shots Triggers:");
  

  while (true) {
    if(Controller1.ButtonA.pressing())
    {
      flywheelSlowA();
    }
    if(Controller1.ButtonB.pressing())
    {
      flywheelSlowB();
    }
    if(Controller1.ButtonY.pressing())
    {
      flywheelSlowY();
    }
    setFly(flywheelState);
    //Flywheel.spin(fwd, flywheelState, voltageUnits::mV); //spins flywheel at top speed
    tempCheck();

    if(Controller1.ButtonL1.pressing())
    {
      Intake.spin(fwd, 12000, voltageUnits::mV);
    }
    if(Controller1.ButtonL2.pressing())
    {
      Intake.stop();
    }

    Controller1.ButtonR2.pressed(shoot);//shoots disc when right bumper 2 is pressed
    //Controller1.ButtonDown.pressed(expand(endgame()));
    
    //if(Controller1.ButtonDown.pressing()) expand(endGame());
    //if(Controller1.ButtonDown.pressing()) Controller1.Screen.print("End Attempt");
    if(Controller1.ButtonDown.pressing())
    {
      expand(Controller2.ButtonDown.pressing());
      Controller1.Screen.print("End Attempt");
    }
    
    
    Controller1.ButtonL1.pressed(rollerSpin);
    Controller1.ButtonL2.pressed(rollerStop);


    frontLeft.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
    rearLeft.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
    frontRight.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);
    rearRight.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);

    Brain.Screen.setCursor(5,1);
    Brain.Screen.print((Flywheel.velocity(rpm) * 6));//prints fhlywheel rpm
    Brain.Screen.setCursor(7,1);
    Brain.Screen.print((Flywheel.temperature(celsius)));//prints flywheel temp
    //Brain.Screen.setCursor(8,1);
    //Brain.Screen.print((FlywheelRear.temperature(celsius)));
    
    Roller.spin(forward, Controller1.Axis3.position(), percent);
  
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

bool isEvil = false;

//
// Main will set up the competition functions and callbacks.
//
int main() {

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    if(isEvil)
    {
      Brain.Screen.setFillColor(red);
    }
    else
    {
      Brain.Screen.setFillColor(blue);
    }
    wait(100, msec);
  }
}








/* useful stuff

Notice that the Vision Sensor has a resolution for 316 pixels horizontally by 212 pixels vertically.
Because the Vision Sensor's resolution is 316 by 212, the maximum range of detection is 0 to 315 on the X-axis and
0 to 211 on the Y-axis.

*/