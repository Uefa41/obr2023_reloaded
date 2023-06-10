#ifndef _CALIBRATION_H
#define _CALIBRATION_H

#include "rgb_set.h"
#include "button.h"
#include "gyro.h"
#include "led.h"

#include <EEPROM.h>

void calibrate(Button &button, RgbSet &rgbSet, Gyro &gyro, Led &led, int iter);

void storeCalibration(RgbSet &rgbSet);

void loadCalibration(RgbSet &rgbSet);

#endif
