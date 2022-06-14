#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
triport Expander19 = triport(PORT19);
motor frontLeft = motor(PORT5, ratio18_1, false);
motor rearLeft = motor(PORT2, ratio18_1, false);
motor frontRight = motor(PORT3, ratio18_1, true);
motor rearRight = motor(PORT4, ratio18_1, true);
controller Controller1 = controller(primary);
/*vex-vision-config:begin*/
signature Vision20__SIG_1 = signature (1, -2893, -2159, -2526, 8305, 12523, 10414, 3, 0);
signature Vision20__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision20__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision20__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision20__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision20__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision20__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision20 = vision (PORT20, 35, Vision20__SIG_1, Vision20__SIG_2, Vision20__SIG_3, Vision20__SIG_4, Vision20__SIG_5, Vision20__SIG_6, Vision20__SIG_7);
/*vex-vision-config:end*/
digital_out Piston = digital_out(Brain.ThreeWirePort.A);
motor FlywheelFront = motor(PORT16, ratio6_1, false);
motor FlywheelRear = motor(PORT18, ratio6_1, false);
motor_group Flywheel = motor_group(FlywheelFront, FlywheelRear);

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