#ifndef _LED_H
#define _LED_H

#include <Arduino.h>

class Led {
  private:

  const byte pinR, pinG, pinB;

  public:

  Led(byte pinR, byte pinG, byte pinB);

  void begin();

  void setRGB(byte R, byte G, byte B);
};

#endif
