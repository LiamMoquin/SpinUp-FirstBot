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


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

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



void autonomous(void) {
  visionStrafe(45);
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

void usercontrol(void) {
  // User control code here, inside the loop
  double Ch3 = Controller1.Axis3.position(percent);
  double Ch4 = Controller1.Axis4.position(percent);
  double Ch1 = Controller1.Axis1.position(percent);

  while (true) {

    Flywheel.spin(fwd, 12000, voltageUnits::mV);
    tempCheck();

    if (Controller1.ButtonR2.pressing())
    {
      shoot();
    }
    Ch3 = Controller1.Axis3.position(percent);
    Ch4 = Controller1.Axis4.position(percent);
    Ch1 = Controller1.Axis1.position(percent);

    frontLeft.setVelocity(Ch3+Ch4+Ch1, percent);
    rearLeft.setVelocity(Ch3-Ch4+Ch1, percent);
    frontRight.setVelocity(Ch3-Ch4-Ch1, percent);
    rearRight.setVelocity(Ch3+Ch4-Ch1, percent);

    frontLeft.spin(forward);
    rearLeft.spin(forward);
    frontRight.spin(forward);
    rearRight.spin(forward);
    Brain.Screen.setCursor(5,1);
    Brain.Screen.print((Flywheel.velocity(rpm) * 6));
    Brain.Screen.setCursor(7,1);
    Brain.Screen.print((FlywheelFront.temperature(celsius)));
    //Brain.Screen.setCursor(8,1);
    //Brain.Screen.print((FlywheelRear.temperature(celsius)));
    
    
  
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

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
    wait(100, msec);
  }
}








/* useful stuff

Notice that the Vision Sensor has a resolution for 316 pixels horizontally by 212 pixels vertically. Because the Vision Sensor's resolution is 316 by 212, the maximum range of detection is 0 to 315 on the X-axis and 0 to 211 on the Y-axis.

*/