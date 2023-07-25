#include "main.h"

Drive chassis ({3, 1}, {-12, -2}, 4, 4.125, 200, 1);
pros::Motor catapult(10);

void initialize() {
  ez::print_ez_template();
  pros::delay(500);
  chassis.toggle_modify_curve_with_controller(false);
  chassis.set_active_brake(0.1);
  chassis.set_curve_default(0, 0); 
  default_constants();
  exit_condition_defaults();
  ez::as::auton_selector.add_autons({
    Auton("Main Auton", main_test_auton)
  });
  chassis.initialize();
  ez::as::initialize();
}

void disabled() {
  // . . .
}

void competition_initialize() {
  // . . .
}

void autonomous() {
  chassis.reset_pid_targets();
  chassis.reset_gyro();
  chassis.reset_drive_sensor();
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
  ez::as::auton_selector.call_selected_auton();
}

void opcontrol() {
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  while (true) {
    if (master.get_digital(DIGITAL_R2)) {
      catapult.move(-127);
    } else {
      catapult.brake();
    }
    chassis.arcade_standard(ez::SPLIT);
    pros::delay(ez::util::DELAY_TIME);
  }
}
