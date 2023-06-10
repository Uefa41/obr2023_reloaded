#include "gyro.h"
#include <Arduino.h>

Gyro::Gyro(byte pin, int ROT_90) : pin(pin), ROT_90(ROT_90) {}

void Gyro::calibrate(int iter) {
  zeroSpeed = 0;

  for (int i = 0; i < iter; i++) {
    zeroSpeed += analogRead(pin);
  }

  zeroSpeed /= iter;

  time = millis();
}

void Gyro::reset() {
  rot = 0;
  time = millis();
}

int Gyro::getSpeed() {
  return analogRead(pin) - zeroSpeed;
}

float Gyro::getRot() {
  rot += (float) (getSpeed() * ((signed long) (millis() - time))) / 100;

  time = millis();

  return rot;
}

void Gyro::waitRot(int rot) {
  reset();
  while (abs(getRot()) < rot);
}
