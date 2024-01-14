#include "main.h"
#define DRIVE_LEFT_A 7
#define DRIVE_LEFT_B 6
#define DRIVE_RIGHT_A 10
#define DRIVE_RIGHT_B 9
#define DRIVE_IMU 8
#define DRIVE_WHEEL_DIAMETER 4.125
#define DRIVE_RPM 600
#define DRIVE_GEAR_RATIO 1
// #define PORT_CATA_A 2
// #define PORT_CATA_B 3
#define PORT_INTAKE_LEFT 11
#define PORT_INTAKE_RIGHT 12
// #define PORT_WINCH 5
// #define PORT_LIMIT 'A'
#define SPEED_INTAKE 127
// #define SPEED_WINCH 35
// #define SPEED_CATA 127
#define ACTIVE_BRAKE_kP 0.1
#define JOYSTICK_LEFT_CURVE 4.05
#define JOYSTICK_RIGHT_CURVE 4.05

Drive chassis ({-DRIVE_LEFT_A,  -DRIVE_LEFT_B}, {DRIVE_RIGHT_A, DRIVE_RIGHT_B}, DRIVE_IMU, DRIVE_WHEEL_DIAMETER, DRIVE_RPM, DRIVE_GEAR_RATIO);
// pros::Motor cataA(PORT_CATA_A);
// pros::Motor cataB(PORT_CATA_B);
pros::Motor intakeL(PORT_INTAKE_LEFT);
pros::Motor intakeR(PORT_INTAKE_RIGHT);
// pros::Motor winch(PORT_WINCH);
// pros::ADIButton limit_switch(PORT_LIMIT);
bool drive_dir_fwd = true;
/* bool l1Clicked = false;
bool l2Clicked = false;
bool goingBack = false;
bool loadedCata = false;
int cataState = 0; */

void initialize() {
  pros::delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_curve_default(JOYSTICK_LEFT_CURVE, JOYSTICK_RIGHT_CURVE);
  chassis.set_active_brake(ACTIVE_BRAKE_kP);
  default_constants();
  exit_condition_defaults();
  chassis.initialize();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  intakeL.set_brake_mode(MOTOR_BRAKE_COAST);
  intakeR.set_brake_mode(MOTOR_BRAKE_COAST);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  // opponent_side();
  // alliance_side();
  blank_auton();
}

void opcontrol() {
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  while (true) {
    chassis.arcade_standard(ez::SPLIT);
    if (master.get_digital(DIGITAL_L2)) {
      intakeL.move(SPEED_INTAKE);
      intakeR.move(-SPEED_INTAKE);
    } else if (master.get_digital(DIGITAL_L1)) {
      intakeL.move(-SPEED_INTAKE);
      intakeR.move(SPEED_INTAKE);
    } else {
      intakeL.brake();
      intakeR.brake();
    }
    if (master.get_digital_new_press(DIGITAL_Y)) {
      if (drive_dir_fwd) {
        chassis.left_motors[0].set_reversed(false);
        chassis.left_motors[1].set_reversed(false);
        chassis.right_motors[0].set_reversed(true);
        chassis.right_motors[1].set_reversed(true);
        drive_dir_fwd = false;
      } else {
        chassis.left_motors[0].set_reversed(true);
        chassis.left_motors[1].set_reversed(true);
        chassis.right_motors[0].set_reversed(false);
        chassis.right_motors[1].set_reversed(false);
        drive_dir_fwd = true;
      }
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}
