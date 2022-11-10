#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
triport Expander19 = triport(PORT19);
motor frontLeft = motor(PORT9, ratio18_1, false);
motor rearLeft = motor(PORT4, ratio18_1, false);
motor frontRight = motor(PORT10, ratio18_1, true);
motor rearRight = motor(PORT3, ratio18_1, true);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
vision::signature Vision20__SIG_1 (1, -4215, -3417, -3816, -2891, -1981, -2436, 3.000, 0);
vision::signature Vision20__SIG_2 (2, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature Vision20__SIG_3 (3, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature Vision20__SIG_4 (4, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature Vision20__SIG_5 (5, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature Vision20__SIG_6 (6, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision::signature Vision20__SIG_7 (7, 0, 0, 0, 0, 0, 0, 3.000, 0);
vision Vision20 = vision (PORT20, 35, Vision20__SIG_1, Vision20__SIG_2, Vision20__SIG_3, Vision20__SIG_4, Vision20__SIG_5, Vision20__SIG_6, Vision20__SIG_7);
/*vex-vision-config:end*/
digital_out Piston = digital_out(Brain.ThreeWirePort.A);
motor Flywheel = motor(PORT5, ratio6_1, true);
motor Roller = motor(PORT6, ratio6_1, false);
motor Intake = motor(PORT14, ratio6_1, true);

optical OpticalSensor = optical(PORT7, false);
inertial imu = inertial(PORT15);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}