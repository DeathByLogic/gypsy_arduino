#include "encoders.h"

//
// Global variables
//

//const float pi = 3.14159;

// Encoder Counts
volatile int count_l;
volatile int count_r;

// Calculated Posistion & Heading
//float sense_speed;
float sense_x = 0.0;
float sense_y = 0.0;
float sense_theta = 0.0;

// Init encoder pins and configure interupts
void encoders_init() {
  // Change encoder pins to input
  pinMode(ENC_RIGHT_A_PIN, INPUT);
  pinMode(ENC_RIGHT_B_PIN, INPUT);
  pinMode(ENC_LEFT_B_PIN, INPUT);
  pinMode(ENC_LEFT_A_PIN, INPUT);
  
  // Change encoder debug pins to output
  pinMode(ENC_DEBUG_L, OUTPUT);
  pinMode(ENC_DEBUG_R, OUTPUT);
  
  // Attach interupt pins to encoder functions
  attachInterrupt(ENC_RIGHT_A_INT, encoders_r, CHANGE);
  attachInterrupt(ENC_RIGHT_B_INT, encoders_r, CHANGE);
  attachInterrupt(ENC_LEFT_A_INT, encoders_l, CHANGE); 
  attachInterrupt(ENC_LEFT_B_INT, encoders_l, CHANGE);
}

// Update the calulated posistion with new data
void update_location() {
  float theta_l;
  float theta_r;
  float theta_sum;
  
  // Left Wheel
  theta_l = ((float)count_l * WHEEL_DIM * pi / ENC_COUNT) / WHEEL_BASE;
  count_l = 0;
  
  sense_x += 0.5 * WHEEL_BASE * (sin(sense_theta + theta_l) - sin(sense_theta));
  sense_y -= 0.5 * WHEEL_BASE * (cos(sense_theta) - cos(sense_theta - theta_l));
  
  // Right Wheel
  theta_r = ((float)count_r * WHEEL_DIM * pi / ENC_COUNT) / WHEEL_BASE;
  count_r = 0;
  
  sense_x += 0.5 * WHEEL_BASE * (sin(sense_theta + theta_r) - sin(sense_theta));
  sense_y += 0.5 * WHEEL_BASE * (cos(sense_theta) - cos(sense_theta + theta_r));

  theta_sum += sense_theta + (theta_l - theta_r);
  
  if (theta_sum > pi)
    theta_sum -= 2 * pi;
    
  if (theta_sum < -pi) 
    theta_sum += 2 * pi;
  
  sense_theta = theta_sum;
}

// Interupt service routine for right wheel encoder
void encoders_l() {
  static EncoderState current_state = STATE_FW_A;
  static EncoderState next_state = STATE_FW_A;
  
  // state of encoder sensor
  boolean A;
  boolean B;

  // read current state of wheel sensors
  A = digitalRead(ENC_LEFT_A_PIN);
  B = digitalRead(ENC_LEFT_B_PIN);
  
  // update state based on new wheel sensor reading
  switch (current_state) {
    case STATE_FW_A:
    case STATE_RV_A:
      if (!A & B) {
        next_state = STATE_FW_B;
      } else if (A & !B) {
        next_state = STATE_RV_D;
      } else {
        next_state = current_state;
      }
      
      break;
    case STATE_FW_B:
    case STATE_RV_B:
      if (!A & !B) {
        next_state = STATE_FW_C;
      } else if (A & B) {
        next_state = STATE_RV_A;
      } else {
        next_state = current_state;
      }
      
      break;
    case STATE_FW_C:
    case STATE_RV_C:
      if (A & !B) {
        next_state = STATE_FW_D;
      } else if (!A & B) {
        next_state = STATE_RV_B;
      } else {
        next_state = current_state;
      }
      
      break;
    case STATE_FW_D:
    case STATE_RV_D:
      if (A & B) {
        next_state = STATE_FW_A;
      } else if (!A & !B) {
        next_state = STATE_RV_C;
      } else {
        next_state = current_state;
      }
      
      break;
    default:
      next_state = STATE_FW_A;
  }
  
  // determine if state has changed and if moving forward or reverse
  if (next_state != current_state) {
    if ((next_state == STATE_FW_A) || (next_state == STATE_FW_B) || (next_state == STATE_FW_C) || (next_state == STATE_FW_D)) {
      count_l += 1;
    } else {
      count_l -= 1;
    }
  } else {
    count_l += 0;
  }
  
  // Change States
  current_state = next_state;
}

// Interupt service routine for left wheel encoder
void encoders_r() {
  static EncoderState current_state = STATE_FW_A;
  static EncoderState next_state = STATE_FW_A;
  
  // state of encoder sensor
  boolean A;
  boolean B;
  
  // read current state of wheel sensors
  A = digitalRead(ENC_RIGHT_A_PIN);
  B = digitalRead(ENC_RIGHT_B_PIN);
  
  // update state based on new wheel sensor reading
  switch (current_state) {
    case STATE_FW_A:
    case STATE_RV_A:
      if (A & !B) {
        next_state = STATE_FW_D;
      } else if (!A & B) {
        next_state = STATE_RV_B;
      } else {
        next_state = current_state;
      }

      break;
    case STATE_FW_B:
    case STATE_RV_B:
      if (A & B) {
        next_state = STATE_FW_A;
      } else if (!A & !B) {
        next_state = STATE_RV_C;
      } else {
        next_state = current_state;
      }

      break;
    case STATE_FW_C:
    case STATE_RV_C:
      if (!A & B) {
        next_state = STATE_FW_B;
      } else if (A & !B) {
        next_state = STATE_RV_D;
      } else {
        next_state = current_state;
      }
      
      break;
    case STATE_FW_D:
    case STATE_RV_D:
      if (!A & !B) {
        next_state = STATE_FW_C;
      } else if (A & B) {
        next_state = STATE_RV_A;
      } else {
        next_state = current_state;
      }
      
      break;
    default:
      next_state = STATE_FW_A;
  }
  
  // determine if state has changed and if moving forward or reverse
  if (next_state != current_state) {
    if ((next_state == STATE_FW_A) || (next_state == STATE_FW_B) || (next_state == STATE_FW_C) || (next_state == STATE_FW_D)) {
      count_r += 1;
    } else {
      count_r -= 1;
    }
  } else {
    count_r += 0;
  }
  
  // Change States
  current_state = next_state;
}
