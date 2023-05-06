#include "motors.h"

#include <Arduino.h>

Motor::Motor(byte pinA, byte pinB, byte pinS)
 : pinA(pinA), pinB(pinB), pinS(pinS) {}

void Motor::begin() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinS, OUTPUT);

  stop();
}

void Motor::spin(int speed) {
  analogWrite(pinS, abs(speed));
  digitalWrite(pinA, speed > 0 ? HIGH : LOW);
  digitalWrite(pinB, speed < 0 ? HIGH : LOW);
}

void Motor::stop() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
}

void Motor::brake() {
  digitalWrite(pinS, HIGH);
  digitalWrite(pinA, HIGH);
  digitalWrite(pinB, HIGH);
}
