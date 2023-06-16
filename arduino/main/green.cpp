#include "green.h"
#include "rgb_set.h"
#include "traction.h"

#include <Arduino.h>

Green::Green(Traction &traction, RgbSet &rgbSet, Gyro &gyro, Led &led, byte noise) : traction(traction), rgbSet(rgbSet), gyro(gyro), led(led), noise(noise) {}

void Green::checkGreen(int count) {
  if (! (rgbSet.greenMask & (LEFT_BIT | RIGHT_BIT)))
    return;

  traction.backwards(traction.minSpeed);
  delay(50);

  traction.stop();

  traction.forward(traction.minSpeed);
  delay(150);

  traction.forward(traction.minSpeed);
  int leftCount = 0, rightCount = 0, mask = 0;
  unsigned long time = millis();
  while (millis() - time < 50) {
    if (rgbSet.rgbLeft.inRange(rgbSet.greenRange, rgbSet.greenMargin)) {
      leftCount++;
      mask;
    }

    if (rgbSet.rgbRight.inRange(rgbSet.greenRange, rgbSet.greenMargin)) {
      rightCount++;
    }

  }

  led.setRGB(0, 255, 0);
  delay(1000);
  led.setRGB(0, 0, 0);
}
