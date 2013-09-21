#include "robot.h"
#include "navigation.h"
#include "double_list.h"
#include "serial.h"

const float pi = 3.14159;

double ct_target = 0.0;
double ct_error = 0.0;

// Current waypoint
DoubleNode<point> *current_waypoint;

// Current Robot Speed & Direction
extern double robot_speed;
extern double robot_dir;

// Current Robot Location
extern float sense_x;
extern float sense_y;
extern float sense_theta;

// Navigation Variables
extern point box_path[];
extern point fig8_path[];

extern DoubleList<point> route;

// Program Setup Function
void setup() { 
  robot_init();       // Init Robot pins and setting
  pid_init();         // Init Control Loop
  motor_init();       // Init Motor Control   
  encoders_init();    // Init Wheel Encoders
  serial_init();      // Init Serial Debug
  
  // Set default speed of motors
  robot_speed = 0.0;
  robot_dir = 0.0;
  
  // wait for start button
  while(!digitalRead(START_BUTTON_PIN))
    delay(10);

  fill_route(&route, box_path, 16);

  //serial_print_path(&route);
  
  //serial_print_pointers(&route);

  smooth_path(&route, 0.00001, 0.5, 0.25);
  
  //serial_print_path(&route);
  
  // Set starting point
  current_waypoint = route.first();
}

// Main Program Loop
void loop() {
  static unsigned long serial_time = 0;
  
  // Run the robot
  run_robot();

  // Print Locations every so often
  if (millis() > serial_time) {
    serial_write_location();    
    //serial_print_location();
    
    serial_time += 100;
  }
} 

// Init the robot variables
void robot_init() {
  // change start button pin to input
  pinMode(START_BUTTON_PIN, INPUT);
}

// Main robot loop
void run_robot() {
  if (current_waypoint == route.last()) {
    // If at last waypoint stop
    robot_speed = 0.0;
  } else {
    // Maintain current speed
    robot_speed = 25.0;
    
     // Update the current location
    update_location();
   
    // Calculate the error value
    ct_error = calculate_cte(current_waypoint, sense_x, sense_y);
    //ct_error = sense_y;
    
    // Run the control loop
    pid_control_loop();
  }
  
  // Update h-bridge output
  motor_update(robot_speed, robot_dir);
}

// How much free RAM is there
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
