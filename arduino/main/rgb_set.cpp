#include "rgb_set.h"
#include "rgb.h"

#include <Arduino.h>

RgbSet::RgbSet(Rgb &rgbLeft, Rgb &rgbRight, Rgb &rgbMid, long greenMargin, long blackMargin, long whiteMargin)
 : rgbLeft(rgbLeft), rgbRight(rgbRight), rgbMid(rgbMid), greenMargin(greenMargin), blackMargin(blackMargin), whiteMargin(whiteMargin) {}

void RgbSet::begin() {
  rgbLeft.begin();
  rgbRight.begin();
  rgbMid.begin();
}

void RgbSet::receiveMasks() {
  greenMask = 0;
  blackMask = 0;
  whiteMask = 0;
  rawRgb states[3];

  rgbLeftLast = states[0] = rgbLeft.getRgbState();
  rgbRightLast = states[1] = rgbRight.getRgbState();
  rgbMidLast = states[2] = rgbMid.getRgbState();

  uint8_t i;
  for (i = 0; i < 3; i++) {
    greenMask <<= 1;
    blackMask <<= 1;
    whiteMask <<= 1;
    greenMask |= (rgbInRange(states[i], greenRange, greenMargin) ? 1 : 0);
    blackMask |= (rgbInRange(states[i], blackRange, blackMargin) ? 1 : 0);
    whiteMask |= (rgbInRange(states[i], whiteRange, whiteMargin) ? 1 : 0);
  }
}
