#ifndef _LINE_H
#define _LINE_H

#include "output/motors.h"
#include "output/traction.h"
#include "input/rgb.h"
#include "input/rgb_set.h"
#include "util/pid.h"

#include <Arduino.h>

class LineFollow {
  private:

  Traction &traction;
  RgbSet &rgbSet;
  Pid &linePID;

  bool lastMid = false;

  public:

  LineFollow(Traction &traction, RgbSet &rgbSet, Pid &linePID);

  void followLine(int baseSpeed, float speedReduc);

  void ninetyDegrees(int minErr);
};

#endif
