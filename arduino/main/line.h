#ifndef _LINE_H
#define _LINE_H

#include "motors.h"
#include "traction.h"
#include "rgb.h"
#include "rgb_set.h"
#include "pid.h"
#include "gyro.h"

#include <Arduino.h>

class LineFollow {
  private:

  Traction &traction;
  RgbSet &rgbSet;
  Pid &linePID;
  Gyro &gyro;

  bool lastMid = false;

  public:

  LineFollow(Traction &traction, RgbSet &rgbSet, Pid &linePID, Gyro &gyro);

  void followLine(int baseSpeed, float speedReduc);

  void ninetyDegrees(int minErr);
};

#endif
