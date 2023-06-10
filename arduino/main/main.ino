/* -- Includes -- */

#include "pins.h"
#include "rgb.h"
#include "rgb_set.h"
#include "gyro.h"
#include "motors.h"
#include "traction.h"
#include "line.h"
#include "button.h"
#include "led.h"
#include "calibration.h"


/* -- Defines -- */
#define CALIBRATION_SAVE
#define TEST


/* -- Constantes -- */

// Velocidade
const int MAX_SPEED = 120;
const int MIN_SPEED = 25;
const int BASE_SPEED = 30;
const int SPIN_SPEED = 85;
const float SR = 0.5;

// Identificação de cores
const int GREEN_MARGIN = 10;
const int GREEN_MARGIN_LF = 7;
const int BLACK_MARGIN = 60;
const int WHITE_MARGIN = 40;
const int MIN_90_ERR = 20;

// Giroscópio
const int ROT_90 = 4000;

// Parâmetros PID
const float KP = 0.0004;
const float KI = 0.00001;
const float KD = 0.00005;
const float MAX_I = 50;


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


// Giroscópio
Gyro gyro(GYRO, ROT_90);


// Botão
Button button(BUTTON);


// LED
Led led(LED_R, LED_G, LED_B);


// Segue-faixa e 90 graus
Pid linePID(KP, KI, KD, MAX_I);

LineFollow line(traction, rgbSet, linePID, gyro);


/* -- Funções -- */

void setup() {
  // Inicialização dos componentes
  rgbSet.begin();
  traction.begin();
  led.begin();
  Serial.begin(9600);

#if defined(CALIBRATION_SAVE)
  if (button.rawValue()) {
    led.setRGB(255, 0, 0);
    while (button.rawValue());

    calibrate(button, rgbSet, gyro, led, 1000);

    storeCalibration(rgbSet);
  } else {
    loadCalibration(rgbSet);
  }
#else
  calibrate(button, rgbSet, gyro, led, 1000);
#endif
}

void loop() {
  rgbSet.receiveMasks();

#if !defined(TEST)
  line.followLine(BASE_SPEED, SR);
  line.ninetyDegrees(MIN_90_ERR);
#else
   //Serial.print(rgbSet.blackMask & 1);
   //Serial.print((rgbSet.blackMask & 2) >> 1);
   //Serial.println((rgbSet.blackMask & 4) >> 2);
  Serial.print("E: ");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.print(rgbSet.rgbLeft.getChannel((Rgb::Channel) i));
    Serial.print(", ");
  }
  Serial.print("; M: ");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.print(rgbSet.rgbMid.getChannel((Rgb::Channel) i));
    Serial.print(", ");
  }
  Serial.print("; D: ");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.print(rgbSet.rgbRight.getChannel((Rgb::Channel) i));
    Serial.print(", ");
  }
  Serial.print("\n");
#endif
}
