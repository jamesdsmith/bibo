#ifndef __IRSENSOR_H__
#define __IRSENSOR_H__
#include "Statemachine.h"

class IRSensor {
public:
  IRSensor(int sensorPin);
  IRSensor(int sensorPin, int numWindows);
  void waitForTurns(float numTurns);
  void waitForTicks(float numTicks);
  int getTurnCount();
  int getTickCount();
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
