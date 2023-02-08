using namespace vex;
extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern motor frontLeft;
extern motor rearLeft;
extern motor frontRight;
extern motor rearRight;
extern controller Controller1;
extern controller Controller2;
extern signature Vision20__SIG_1;
extern signature Vision20__SIG_2;
extern signature Vision20__SIG_3;
extern signature Vision20__SIG_4;
extern signature Vision20__SIG_5;
extern signature Vision20__SIG_6;
extern signature Vision20__SIG_7;
extern vision Vision20;
extern triport Expander19;
extern digital_out Piston;
extern digital_out Expansion;
extern digital_out Expansion2;
extern motor Flywheel;
extern motor Roller;
extern motor IntakeLeft;
extern motor IntakeRight;
extern motor_group Intake;
extern optical OpticalSensor;
extern inertial imu;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );