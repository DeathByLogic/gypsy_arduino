#ifndef _ENCODERS_H
#define _ENCODERS_H

//Function Prototypes
void encoders_init();
void update_location();
void encoders_l();
void encoders_r();

// Constant Definitions
#define ENC_LEFT_A_PIN   18
#define ENC_LEFT_B_PIN   19
#define ENC_RIGHT_A_PIN  20
#define ENC_RIGHT_B_PIN  21

#define ENC_LEFT_A_INT   5
#define ENC_LEFT_B_INT   4
#define ENC_RIGHT_A_INT  3
#define ENC_RIGHT_B_INT  2

#define ENC_DEBUG_L      22
#define ENC_DEBUG_R      23

#define WHEEL_BASE 13.25      // Distance between wheels
#define WHEEL_DIM  4.875      // Diamater of wheels
#define ENC_COUNT  100        // Number of encoder counts per revolution
//#define PI         3.14159    // PI contstant

// Type Definitions
typedef enum {
  STATE_FW_A,
  STATE_FW_B,
  STATE_FW_C,
  STATE_FW_D,
  STATE_RV_A,
  STATE_RV_B,
  STATE_RV_C,
  STATE_RV_D
} EncoderState;

#endif
