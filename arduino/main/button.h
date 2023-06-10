#ifndef _BUTTON_H
#define _BUTTON_H

#include <Arduino.h>

class Button {
  private:

  const byte pin;

  bool state = false, lastReading = false;

  unsigned long time = 0, minTime = 0;

  public:

  Button(byte pin);
  void begin();

  bool rawValue();

  void update();

  bool getState();

  void waitPress();
};

#endif
