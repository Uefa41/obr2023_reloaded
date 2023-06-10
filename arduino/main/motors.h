#ifndef _MOTORS_H
#define _MOTORS_H

#include <Arduino.h>

class Motor {
  private:

  const byte pinA, pinB, pinS;

  public:

  Motor(byte pinA, byte pinB, byte pinS);

  void begin();

  void spin(int speed);

  void stop();

  void brake();
};

#endif
