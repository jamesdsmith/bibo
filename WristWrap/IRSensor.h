#ifndef __IRSENSOR_H__
#define __IRSENSOR_H__
#include "Statemachine.h"

class IRSensor {
public:
  IRSensor(int sensorPin);
  IRSensor(int sensorPin, int numWindows);
  void waitForTurns(float numTurns);
  int getTurnCount();
  void sample();
private:
  int numWindows;
  Statemachine counter;
  int turnCount = 0;
  int tickCount = 0;
  int sensorPin;
  int sampleRate = 100;
};
#endif
