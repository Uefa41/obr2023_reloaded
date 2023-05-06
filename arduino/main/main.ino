/* -- Includes -- */

#include "pins.h"
#include "input/rgb.h"
#include "input/rgb_set.h"
#include "output/motors.h"
#include "output/traction.h"
#include "line.h"


/* -- Constantes -- */

// Velocidade
const int MAX_SPEED = 120;
const int MIN_SPEED = 35;
const int BASE_SPEED = 40;
const int SPIN_SPEED = 85;
const float SR = 0.2;

// Identificação de cores
const int GREEN_MARGIN = 10;
const int GREEN_MARGIN_LF = 7;
const int BLACK_MARGIN = 10;
const int WHITE_MARGIN = 10;
const int MIN_90_ERR = 100;


/* -- Declaração dos componentes -- */

// RGBs
Rgb rgbLeft(RGB_L_S0, RGB_L_S1, RGB_L_S2, RGB_L_S3, RGB_L_OUT);
Rgb rgbRight(RGB_R_S0, RGB_R_S1, RGB_R_S2, RGB_R_S3, RGB_R_OUT);
Rgb rgbMid(RGB_M_S0, RGB_M_S1, RGB_M_S2, RGB_M_S3, RGB_M_OUT);
RgbSet rgbSet(rgbLeft, rgbRight, rgbMid, GREEN_MARGIN, BLACK_MARGIN, WHITE_MARGIN);

// Tração
Motor motorBackLeft(MOTOR_BL_IN1, MOTOR_BL_IN2, MOTOR_BL_S);
Motor motorBackRight(MOTOR_BR_IN1, MOTOR_BR_IN2, MOTOR_BR_S);
Motor motorFrontLeft(MOTOR_FL_IN1, MOTOR_FL_IN2, MOTOR_FL_S);
Motor motorFrontRight(MOTOR_FR_IN1, MOTOR_FR_IN2, MOTOR_FR_S);

Traction traction(motorFrontLeft, motorFrontRight, motorBackLeft,
 motorBackRight, MIN_SPEED, MAX_SPEED, BASE_SPEED, SPIN_SPEED);


/* -- Funções -- */

void setup() {
  // Inicialização dos componentes
  rgbSet.begin();
}

void loop() {
  rgbSet.receiveMasks();
}
