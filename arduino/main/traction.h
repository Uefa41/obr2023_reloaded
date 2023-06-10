#ifndef _TRACTION_H
#define _TRACTION_H

#include "motors.h"

#include <Arduino.h>

class Traction {
  private:

  Motor &motorFrontLeft;
  Motor &motorFrontRight;
  Motor &motorBackLeft;
  Motor &motorBackRight;

  public:

  const int maxSpeed, minSpeed, baseSpeed, spinSpeed;

  Traction(Motor &motorFrontLeft, Motor &motorFrontRight, Motor &motorBackLeft,
     Motor &motorBackRight, int minSpeed, int maxSpeed, int baseSpeed, int spinSpeed);

  void begin();

  void turnDirection(int direction, int baseSpeed);

  void forward(int speed);

  void backwards(int speed);

  void spin(int speed);

  void stop();

  void brake();
};

#endif
