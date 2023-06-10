#ifndef _RGB_H
#define _RGB_H

#include <Arduino.h>

struct rawRgb {
  long values[4];
};

struct rawRgbRange {
  rawRgb l, u;
};

bool rgbInRange(rawRgb state, rawRgbRange range, long margin);

class Rgb {
  private:

  const byte pinS0, pinS1, pinS2, pinS3, pinOut;

  public:

  enum Channel {
    RED = 0,
    BLUE = 1,
    REF = 2,
    GREEN = 3,
  };

  Rgb(byte pinS0, byte pinS1, byte pinS2, byte pinS3, byte pinOut);

  void begin();

  long getChannel(Channel channel, bool lowFreq = false);

  rawRgb getRgbState(bool lowFreq = false);

  rawRgbRange getRgbRange(int iter);

  bool inRange(rawRgbRange range, long margin, bool lowFreq);

  bool rangeDoubleCheck(rawRgbRange range, long margin, int iter);
};

#endif
