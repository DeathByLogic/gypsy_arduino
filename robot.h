#ifndef _ROBOT_H
#define _ROBOT_H

#include "pid.h"

// Function Prototypes
void robot_init();
void run_robot();

#define START_BUTTON_PIN  2
/*
typedef enum {
  FORWARD,
  REVERSE
} Direction;
*/
typedef enum {
  LEFT, 
  RIGHT
} WheelSide;

#endif
