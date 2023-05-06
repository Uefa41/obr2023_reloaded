#ifndef _RGB_SET_H
#define _RGB_SET_H

#include "rgb.h"

#include <Arduino.h>

#define LEFT_BIT 4
#define RIGHT_BIT 2
#define MID_BIT 1

class RgbSet {
  public:

  rawRgbRange greenRange, blackRange, whiteRange;

  Rgb &rgbLeft;
  Rgb &rgbRight;
  Rgb &rgbMid;

  long greenMargin, blackMargin, whiteMargin;

  rawRgb rgbLeftLast;
  rawRgb rgbRightLast;
  rawRgb rgbMidLast;

  byte greenMask, blackMask, whiteMask;

  RgbSet(Rgb &rgbLeft, Rgb &rgbRight, Rgb &rgbMid, long greenMargin, long blackMargin, long whiteMargin);

  void begin();

  void receiveMasks();
};

#endif
