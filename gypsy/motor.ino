#include <Sabertooth.h>
#include "motor.h"

// Global variables
Sabertooth ST(HBRIDGE_ADDRESS, Serial2);

void motor_init() {
  // Init Serial port for H-Bridge
  Serial2.begin(HBRIDGE_BAUD_RATE);
  
  ST.setDeadband(HBRIDGE_DEADBAND);       // Set deadband width
  ST.setMinVoltage(HBRIDGE_MIN_VOLTAGE);  // Set battery cutoff
}

void motor_update(int rbt_speed, int rbt_dir) {
  int mtr_speed;
  int mtr_dir;
  
  // Constrain speed and direction
  rbt_speed = constrain(rbt_speed, SPEED_MIN, SPEED_MAX);
  rbt_dir = constrain(rbt_dir, DIR_MIN, DIR_MAX);
  
  // Scale the values to be used with the motors
  mtr_speed = map(rbt_speed, SPEED_MIN, SPEED_MAX, HBRIDGE_CMD_MIN, HBRIDGE_CMD_MAX);
  mtr_dir = map(rbt_dir, DIR_MIN, DIR_MAX, -mtr_speed, mtr_speed);
  
  ST.drive(mtr_speed);
  ST.turn(mtr_dir);
}
