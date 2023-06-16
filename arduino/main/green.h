#ifndef _GREEN_H
#define _GREEN_H

#include "motors.h"
#include "traction.h"
#include "rgb.h"
#include "rgb_set.h"
#include "gyro.h"
#include "led.h"

#include <Arduino.h>

class Green {
  private:

  Traction &traction;
  RgbSet &rgbSet;
  Gyro &gyro;
  Led &led;
  const byte noise;

  public:

  Green(Traction &traction, RgbSet &rgbSet, Gyro &gyro, Led &led, byte noise);


  void checkGreen(int count);
};

#endif
