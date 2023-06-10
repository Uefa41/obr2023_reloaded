#include "button.h"

#include <Arduino.h>

Button::Button(byte pin) : pin(pin) {}

void Button::begin() {
  pinMode(pin, INPUT);
}

bool Button::rawValue() {
  return digitalRead(pin);
}

void Button::update() {
  bool newReading = rawValue();

  if (newReading != lastReading) {
    time = millis();
  }

  if (millis() - time >= minTime) {
    state = newReading;
  }

  lastReading = newReading;
}

bool Button::getState() {
  update();

  return state;
}

void Button::waitPress() {
  while (!getState());
  while(getState());
}
