#ifndef _GYRO_H
#define _GYRO_H

#include <Arduino.h>

class Gyro {
  private:

  const byte pin;
  unsigned long time;

  int zeroSpeed;

  float rot = 0;

  public:

  const int ROT_90;

  Gyro(byte pin, int ROT_90);

  void calibrate(int iter);

  void reset();

  int getSpeed();

  float getRot();

  void waitRot(int rot);
};

#endif
