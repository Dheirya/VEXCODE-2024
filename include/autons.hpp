#pragma once
#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
extern pros::Motor cataA;
extern pros::Motor cataB;
extern pros::Motor intakeL;
extern pros::Motor intakeR;
extern pros::Motor intake;
extern pros::Motor winch;
extern pros::ADIDigitalIn limit_switch;

void opponent_side();
void alliance_side();
void blank_auton();
void default_constants();
void exit_condition_defaults();
