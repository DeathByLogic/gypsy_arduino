#include <PID_v1.h>
#include <PID_AutoTune_v0.h>
#include "pid.h"

// Glocal Variables
PIDParam tuned_pid = {0.37, 0.02, 2.20};

PIDParam motor_20_pid = {7.00, 1.00, 5.00};
PIDParam motor_50_pid = {1.00, 0.00, 1.50};

PIDParam tuned_50s = {1.45, 0.11, 4.59};
PIDParam tuned_100s = {10.72, 0.90, 31.90};

// Current Robot Speed & Direction
double robot_speed = 0.0;
double robot_dir = 0.0;

// Tuning and has been tuned?
boolean tune_pid = false;
boolean pid_tuned;

extern double ct_error;
extern double ct_target;

//Specify the links and initial tuning parameters
PID myPID(&ct_error, &robot_dir, &ct_target, tuned_50s.Kp, tuned_50s.Ki, tuned_50s.Kd, DIRECT);
PID_ATune aTune(&ct_error, &robot_dir);

void pid_init() {
  // if tuning setup aTune module
  if (tune_pid) {
    // Print start of tuning comment
    Serial.println(":AUTOTUNE START:");
    
    // PID has not yet been tuned
    pid_tuned = false;
    
    // Setup aTune control
    aTune.SetControlType(aTuneType);
    aTune.SetNoiseBand(aTuneNoise);
    aTune.SetOutputStep(aTuneStep);
    aTune.SetLookbackSec(aTuneLookBack);
  }

  // setup PID module
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(SAMPLE_PERIOD); 
  myPID.SetOutputLimits(OUTPUT_MIN, OUTPUT_MAX);
}

void pid_control_loop() {
   if (tune_pid && !pid_tuned) {
    if (aTune.Runtime()) {
      
      // Get tuned PID parameters
      tuned_pid.Kp = aTune.GetKp();
      tuned_pid.Ki = aTune.GetKi();
      tuned_pid.Kd = aTune.GetKd();
      
      // Set tuned PID paramters as active
      myPID.SetTunings(tuned_pid.Kp, tuned_pid.Ki, tuned_pid.Kd);
      
      // Print tuned PID parameters
      Serial.print("kp: ");Serial.print(tuned_pid.Kp);Serial.print(" ");
      Serial.print("ki: ");Serial.print(tuned_pid.Ki);Serial.print(" ");
      Serial.print("kd: ");Serial.print(tuned_pid.Kd);Serial.println(); 
      
      // Print end of autotune comment
      Serial.println(":AUTOTUNE END:"); 
      
      // PID has now been tuned
      pid_tuned = true;
    }
  } else {
    // Run PID calculations
    myPID.Compute();
  } 
}

//
// Old Code
//

/*
// Global Variables
//PIDParam Theta_Param = {26.3663, 4.0130, 1.1822};
PIDParam Theta_PID = {-0.35, 0.0, 0.0};
PIDParam Loc_PID = {0.0, 0.0, 0.0};

// Calculate location based PID
float calc_location_PID(PIDParam PID_Param, float error) {
  static float int_error = 0.0;
  static float pre_error = 0.0;
  
  float drv_error = 0.0;
  float per_error = 0.0;
  
  per_error = error;
  int_error += per_error * SAMPLE_PERIOD;
  drv_error = (per_error - pre_error) / SAMPLE_PERIOD;
  
  pre_error = per_error; 
  
  return PID_Param.Kp * per_error + PID_Param.Ki * int_error + PID_Param.Kd * drv_error;
}

// Calculate theta based PID
float calc_theta_PID(PIDParam PID_Param, float error) {
  static float int_error = 0.0;
  static float pre_error = 0.0;
  
  float drv_error = 0.0;
  float per_error = 0.0;
  
  per_error = error;
  int_error += per_error * SAMPLE_PERIOD;
  drv_error = (per_error - pre_error) / SAMPLE_PERIOD;
  
  pre_error = per_error; 
  
  return PID_Param.Kp * per_error + PID_Param.Ki * int_error + PID_Param.Kd * drv_error;
}
*/
