#include "line.h"
#include "input/rgb.h"
#include "input/rgb_set.h"
#include "output/motors.h"
#include "output/traction.h"
#include "util/pid.h"

#include <Arduino.h>

LineFollow::LineFollow(Traction &traction, RgbSet &rgbSet, Pid &linePID)
 : traction(traction), rgbSet(rgbSet), linePID(linePID) {}

void LineFollow::followLine(int baseSpeed, float speedReduc) {
  float error = sq(rgbSet.rgbRightLast.values[Rgb::REF]) -
   sq(rgbSet.rgbLeftLast.values[Rgb::REF]);

  int direction = linePID.output(error);

  traction.turnDirection(direction, baseSpeed - abs(direction) * speedReduc);
}

void LineFollow::ninetyDegrees(int minErr) {
 lastMid = lastMid || (MID_BIT & rgbSet.blackMask);

 if (!lastMid || !(MID_BIT & rgbSet.whiteMask))
  return;

 lastMid = false;

 traction.forward(traction.baseSpeed);
 float error;
 for (unsigned long time = millis(); millis() - time < 90) {
  error = sq(rgbSet.rgbRightLast.values[Rgb::REF]) -
   sq(rgbSet.rgbLeftLast.values[Rgb::REF]);

  rgbSet.receiveMasks();

  switch (rgbSet.blackMask & (LEFT_BIT | RIGHT_BIT)) {
   case LEFT_BIT:
    
  }
 }
}