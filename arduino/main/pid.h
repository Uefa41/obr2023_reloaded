#ifndef _PID_H
#define _PID_H

#include <Arduino.h>

class Pid {
  private:

  float lastError = 0, P = 0, I = 0, D = 0;
  const float kP, kI, kD, maxI;

  public:

  Pid(float kP, float kI, float kD, float maxI);

  float output(float error);

  void reset();
};

#endif