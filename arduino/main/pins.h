#ifndef PINS_H
#define PINS_H

#include <Arduino.h>

enum Pins {
  /// Ultrasonic
  // Front
  US_ECHO = 47,
  US_TRIG = 46,

  // // Left
  // US_L_ECHO = 27,
  // US_L_TRIG = 26,

  // // Right
  // US_R_ECHO = 24,
  // US_R_TRIG = 25,

  /// RGB sensors
  // Left
  RGB_L_S0 = 36,
  RGB_L_S1 = 37,
  RGB_L_S2 = 39,
  RGB_L_S3 = 38,
  RGB_L_OUT = 40,

  // Right
  RGB_R_S0 = 31,
  RGB_R_S1 = 32,
  RGB_R_S2 = 34,
  RGB_R_S3 = 33,
  RGB_R_OUT = 35,

  // Mid
  RGB_M_S0 = 41,
  RGB_M_S1 = 42,
  RGB_M_S2 = 44,
  RGB_M_S3 = 43,
  RGB_M_OUT = 45,

  /// Motors
  // Left Front
  MOTOR_FL_IN1 = 23,
  MOTOR_FL_IN2 = 24,
  MOTOR_FL_S = 12,

  // Right Front
  MOTOR_FR_IN1 = 25,
  MOTOR_FR_IN2 = 26,
  MOTOR_FR_S = 11,

  // Left Back
  MOTOR_BL_IN1 = 28,
  MOTOR_BL_IN2 = 27,
  MOTOR_BL_S = 10,

  // Right Back
  MOTOR_BR_IN1 = 30,
  MOTOR_BR_IN2 = 29,
  MOTOR_BR_S = 9,

  /// Button
  BUTTON = 22,

  /// LED
  LED_R = 8,
  LED_G = 7,
  LED_B = 6,

  /// Buzzer
  NOISE = 48,

  /// Gyroscope
  GYRO = A8,
};

#endif
