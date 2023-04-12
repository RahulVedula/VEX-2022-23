#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotor = motor(PORT1, ratio18_1, false);
motor leftMotor2 = motor(PORT2, ratio18_1, false);
motor rightMotor = motor(PORT9, ratio18_1, false);
motor rightMotor2 = motor(PORT10, ratio18_1, false);
motor ClawMotor = motor(PORT3, ratio18_1, false);
motor ArmMotor = motor(PORT8, ratio18_1, false);

// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}