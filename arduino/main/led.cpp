#include "led.h"

#include <Arduino.h>

Led::Led(byte pinR, byte pinG, byte pinB) : pinR(pinR), pinG(pinG), pinB(pinB) {}

void Led::begin() {
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  setRGB(0, 0, 0);
}

void Led::setRGB(byte R, byte G, byte B) {
  analogWrite(pinR, 255 - R);
  analogWrite(pinG, 255 - G);
  analogWrite(pinB, 255 - B);
}
