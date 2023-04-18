/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Tue Sep 24 2019                                           */
/*    Description:  Controller Buttons                                        */
/*    This program shows two different ways of controlling robot behavior     */
/*    using Controller buttons.                                               */
/*   - "When Controller" events are triggered when a Controller button is     */
/*     pressed                                                                */
/*   - "If / Else" statements can be used inside of a "true" loop to check    */
/*     if a button pressed and perform different behaviors.                   */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Motor2               motor         2               
// Motor9               motor         9               
// Motor10              motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// Method - 1 Callbacks
// whenControllerL1Pressed and whenControllerL2Pressed callback functions are
// registered to the contorller's button 'pressed' event. Whenever the 'Button
// L1' and 'Button R1` are pressed, the functions will run.

void whenControllerL1Pressed() {
  //Forward Or Reverse
   leftMotor2.spin(reverse);
  rightMotor2.spin(forward);  
    leftMotor.spin(reverse);
  rightMotor.spin(forward);
  waitUntil(!Controller1.ButtonL1.pressing());
  rightMotor2.stop();
  leftMotor2.stop();
  rightMotor.stop();
  leftMotor.stop();
}

void whenControllerL2Pressed() {
  //Forward or Reverse 
  leftMotor2.spin(forward);
  rightMotor2.spin(reverse);  
    leftMotor.spin(forward);
  rightMotor.spin(reverse);
  waitUntil(!Controller1.ButtonL2.pressing());
  rightMotor2.stop();
  leftMotor2.stop();
  rightMotor.stop();
  leftMotor.stop();
}

void whenControllerR1Pressed() {
  //Left Or Right
  leftMotor.spin(forward);
  rightMotor2.spin(reverse);  
  waitUntil(!Controller1.ButtonR2.pressing());
  rightMotor2.stop();
  leftMotor2.stop();
}
void whenControllerR2Pressed() {
  //Forward or Reverse 
  leftMotor2.spin(forward);
  rightMotor2.spin(reverse);  
  waitUntil(!Controller1.ButtonR1.pressing());
  rightMotor2.stop();
  leftMotor2.stop();
}

void whenControllerXPressed() {
  //Forward or Reverse 
  leftMotor2.spin(forward);
  rightMotor2.spin(forward);  
  leftMotor.spin(forward);
  rightMotor.spin(forward);  
  waitUntil(!Controller1.ButtonX.pressing());
  rightMotor2.stop();
  leftMotor2.stop();
  leftMotor.stop();
  rightMotor.stop();  
}

void whenControllerBPressed() {
  //Forward or Reverse 
  leftMotor2.spin(reverse);
  rightMotor2.spin(reverse);  
  leftMotor.spin(reverse);
  rightMotor.spin(reverse);  
  waitUntil(!Controller1.ButtonB.pressing());
  rightMotor2.stop();
  leftMotor2.stop();
  leftMotor.stop();
  rightMotor.stop();  
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Set motor's brake mode and velocity
  leftMotor2.setStopping(hold);
  rightMotor2.setStopping(hold);
  leftMotor.setStopping(hold);
  rightMotor.setStopping(hold);
  // ArmMotor.setVelocity(30, percent);
  // ClawMotor.setVelocity(60, percent);
  leftMotor2.setVelocity(30, percent);
  rightMotor2.setVelocity(30, percent);
  leftMotor.setVelocity(30, percent);
  rightMotor.setVelocity(30, percent);

  // Method 1 - Using Callbacks
  // Register callbacks to controller button 'pressed' events.
  Controller1.ButtonL1.pressed(whenControllerL1Pressed);
  Controller1.ButtonL2.pressed(whenControllerL2Pressed);
  Controller1.ButtonR1.pressed(whenControllerR1Pressed);
  Controller1.ButtonR2.pressed(whenControllerR2Pressed);
  Controller1.ButtonB.pressed(whenControllerBPressed);
  Controller1.ButtonX.pressed(whenControllerXPressed);
//   while (true){
//   if (Controller1.Axis1.position() > 0){
//     whenControllerL2Pressed();
//   }
//   if (Controller1.Axis2.position() < 0){
//     whenControllerL1Pressed();
//   }
// if (Controller1.Axis3.position() > 0){
//     whenControllerR1Pressed();
//   }
//   if (Controller1.Axis4.position() < 0){
//     whenControllerR2Pressed();
//   }
//   wait(25, msec);
//   }

//   // Method - 2 Inline-code
//   // Use a 'forever loop' to constantly check the controller's values.
//   while (true) {
//     if (Controller1.ButtonR1.pressing()) {
//       ClawMotor.spin(forward);
//     } else if (Controller1.ButtonR2.pressing()) {
//       ClawMotor.spin(reverse);
//     } else {
//       ClawMotor.stop();
//     }
//     wait(25, msec);
//   }
}
