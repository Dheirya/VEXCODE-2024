#include "main.h"

const int DRIVE_SPEED = 110;
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;
const int INTAKE_SPEED = 127;
const int WINCH_SPEED = 35;

// https://ez-robotics.github.io/EZ-Template/tutorials/tuning_constants
void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void opponent_side() {
  // ...
}

void alliance_side() {
  // ...
}

void blank_auton() {
  // AT 0deg
  chassis.set_drive_pid(48, DRIVE_SPEED, true);
  chassis.wait_drive();
  // AT 180deg
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(48, DRIVE_SPEED, true);
  chassis.wait_drive();
  // BACK TO 0deg
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}
