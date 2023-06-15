#include "line.h"
#include "rgb.h"
#include "rgb_set.h"
#include "motors.h"
#include "traction.h"
#include "pid.h"

#include <Arduino.h>

LineFollow::LineFollow(Traction &traction, RgbSet &rgbSet, Pid &linePID, Gyro &gyro, Led &led)
 : traction(traction), rgbSet(rgbSet), linePID(linePID), gyro(gyro), led(led) {}

void LineFollow::followLine(int baseSpeed, float speedReduc, float maxDir) {
  float error = sq(rgbSet.rgbRightLast.values[Rgb::REF] / 10.0) -
   sq(rgbSet.rgbLeftLast.values[Rgb::REF] / 10.0);

  float direction = linePID.output(error);

 Serial.println(direction);

  if (abs(direction) > maxDir) {
   traction.spin(traction.spinSpeed * (direction > 0 ? 1 : -1));
  } else {
   traction.turnDirection(direction, baseSpeed * (100 - abs(direction) * speedReduc) / 100);
  }
}

void LineFollow::ninetyDegrees(int minErr) {
 lastMid = lastMid || (MID_BIT & rgbSet.blackMask);

 if (!lastMid || !(MID_BIT & rgbSet.whiteMask))
  return;

 lastMid = false;

 traction.forward(traction.baseSpeed);
 float error;
 for (unsigned long time = millis(); millis() - time < 90; ) {
  error = rgbSet.rgbRightLast.values[Rgb::REF] -
   rgbSet.rgbLeftLast.values[Rgb::REF];

  rgbSet.receiveMasks();

  int dir = rgbSet.blackMask & (LEFT_BIT | RIGHT_BIT);

  if (error > -minErr) {
   dir &= ~LEFT_BIT;
  }
  if (error < minErr) {
   dir &= ~RIGHT_BIT;
  }

  if (! dir)
   continue;

  led.setRGB(0, 0, 255);

  traction.backwards(traction.minSpeed);
  delay(150);

  traction.spin((dir == LEFT_BIT ? -1 : 1) * traction.spinSpeed);
  delay(300);
  rgbSet.receiveMasks();
  if (rgbSet.whiteMask & dir) {
   traction.spin((dir == LEFT_BIT ? 1 : -1) * traction.spinSpeed);
   delay(300);
   traction.forward(traction.minSpeed);
   do {
    rgbSet.receiveMasks();
   } while (rgbSet.whiteMask & MID_BIT);
   return;
  }

  traction.forward(traction.minSpeed);
  for (unsigned long time = millis(); millis() - time < 100;) {
   rgbSet.receiveMasks();
   if ((dir == LEFT_BIT? RIGHT_BIT: LEFT_BIT) & rgbSet.whiteMask) {
    break;
   }
  }
  delay(120);

  traction.backwards(traction.minSpeed);
  delay(50);

  traction.stop();
  delay(500);

  gyro.reset();
  traction.spin((dir == LEFT_BIT ? -1 : 1) * traction.spinSpeed);
  do {
   rgbSet.receiveMasks();
   if (abs(gyro.getRot()) < gyro.ROT_90)
    continue;

   traction.spin((dir == LEFT_BIT ? 1 : -1) * traction.spinSpeed);
   gyro.waitRot(gyro.ROT_90);
   traction.forward(traction.minSpeed);
   delay(50);
   return;
  } while (!(dir & rgbSet.blackMask));

  delay(80);
  traction.spin(traction.spinSpeed);
  delay(50);
  traction.stop();
  delay(50);

  traction.backwards(traction.minSpeed);
  delay(110);
  traction.stop();

  linePID.reset();
  led.setRGB(0, 0, 0);
  return;
 }
}