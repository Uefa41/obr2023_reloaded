#include "calibration.h"
#include "button.h"
#include "rgb_set.h"
#include "gyro.h"
#include "led.h"

#include <Arduino.h>

void calibrate(Button &button, RgbSet &rgbSet, Gyro &gyro, Led &led, int iter) {
  led.setRGB(0, 255, 0);
  button.waitPress();
  gyro.calibrate(iter);
  rgbSet.greenRange = rgbSet.rgbLeft.getRgbRange(iter);

  led.setRGB(0, 0, 255);
  button.waitPress();
  rgbSet.blackRange = rgbSet.rgbLeft.getRgbRange(iter);

  led.setRGB(255, 255, 255);
  button.waitPress();
  rgbSet.whiteRange = rgbSet.rgbLeft.getRgbRange(iter);

  led.setRGB(255, 0, 0);
  button.waitPress();
}

void storeCalibration(RgbSet &rgbSet) {
  int addr = 0;

  EEPROM.put(addr, rgbSet.greenRange);
  addr += sizeof(rgbSet.greenRange);

  EEPROM.put(addr, rgbSet.blackRange);
  addr += sizeof(rgbSet.blackRange);

  EEPROM.put(addr, rgbSet.whiteRange);
  addr += sizeof(rgbSet.whiteRange);
}

void loadCalibration(RgbSet &rgbSet) {
  int addr = 0;

  EEPROM.get(addr, rgbSet.greenRange);
  addr += sizeof(rgbSet.greenRange);

  EEPROM.get(addr, rgbSet.blackRange);
  addr += sizeof(rgbSet.blackRange);

  EEPROM.get(addr, rgbSet.whiteRange);
  addr += sizeof(rgbSet.whiteRange);
}
