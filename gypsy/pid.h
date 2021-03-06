#ifndef _PID_H
#define _PID_H

// Type Definitions
typedef struct {
  float Kp;
  float Ki;
  float Kd;
} PIDParam;

// Function Prototypes
//float calc_location_PID(PIDParam, float);
//float calc_theta_PID(PIDParam, float);

// Constant Definitions

#define SAMPLE_PERIOD    100    // PID Loop period

#define OUTPUT_MIN      -100
#define OUTPUT_MAX       100

// aTune Config
#define aTuneType        1
#define aTuneStep        100.0
#define aTuneNoise       1.0
#define aTuneLookBack    20

#endif
