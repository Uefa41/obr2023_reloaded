#include "rgb.h"

#include <Arduino.h>

Rgb::Rgb(byte pinS0, byte pinS1, byte pinS2, byte pinS3, byte pinOut)
 : pinS0(pinS0), pinS1(pinS1), pinS2(pinS2), pinS3(pinS3), pinOut(pinOut) {}

void Rgb::begin() {
  // Inicializa os pinos
  pinMode(pinS0, OUTPUT);
  pinMode(pinS1, OUTPUT);
  pinMode(pinS2, OUTPUT);
  pinMode(pinS3, OUTPUT);
  pinMode(pinOut, INPUT);
}

long Rgb::getChannel(Channel channel, bool lowFreq) {
  long period;

  // Muda o escalonamento de frequência de acordo com parâmetro 
  digitalWrite(pinS0, lowFreq ? LOW : HIGH);
  digitalWrite(pinS1, lowFreq ? HIGH : LOW);

  /*
    | S2 | S3 | Filtro |
    |----|----|--------|
    |LOW |LOW |Vermelho|
    |LOW |HIGH|  Azul  |
    |HIGH|LOW | Nenhum |
    |HIGH|HIGH| Verde  |
  */
  digitalWrite(pinS2, (channel & 2) ? HIGH : LOW);
  digitalWrite(pinS3, (channel & 1) ? HIGH : LOW);

  // Saída do sensor é medida através do período do pulso
  period = pulseIn(pinOut, digitalRead(pinOut) == LOW ? HIGH : LOW);

  return (lowFreq ? period : period * 10);
}

rawRgb Rgb::getRgbState(bool lowFreq) {
  rawRgb state;

  for (uint8_t i = 0; i < 4; i++) {
    state.values[i] = getChannel((Channel) i, lowFreq);
  }

  return state;
}

rawRgbRange Rgb::getRgbRange(int iter) {
  rawRgb state;
  rawRgbRange range;

  range.u = range.l = state;

  for (int i = 0; i < iter; i++) {
    state = getRgbState(true);
    for (uint8_t j = 0; j < 4; j++) {
      range.l.values[j] = min(range.l.values[j], state.values[j]);
      range.u.values[j] = max(range.l.values[j], state.values[j]);
    }

    delay(1);
  }

  return range;
}

bool rgbInRange(rawRgb state, rawRgbRange range, long margin) {
  bool res = true;

  for (uint8_t i = 0; i < 4; i++) {
    res = res && state.values[i] >= range.l.values[i] - margin &&
       state.values[i] <= range.u.values[i] + margin;

    if (!res)
      return res;
  }

  return res;
}

bool Rgb::inRange(rawRgbRange range, long margin, bool lowFreq) {
  return rgbInRange(getRgbState(lowFreq), range, margin);
}

bool Rgb::rangeDoubleCheck(rawRgbRange range, long margin, int iter, bool lowFreq) {
  int f = 0; // Contador de falhas

  for (int i = 0; i < iter; i++) {
    if (! inRange(range, margin, lowFreq))
      f++;

    if (f > iter / 2)
      return false;
  }

  return true;
}
