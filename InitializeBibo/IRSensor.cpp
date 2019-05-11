#include "Arduino.h"
#include "IRSensor.h"

IRSensor::IRSensor(int sensorPin) {
  this->sensorPin = sensorPin;
  this->numWindows = 20;
  pinMode(this->sensorPin, INPUT);
}

IRSensor::IRSensor(int sensorPin, int numWindows) {
  this->sensorPin = sensorPin;
  this->numWindows = numWindows;
  pinMode(this->sensorPin, INPUT);
}

void IRSensor::waitForTurns(float numTurns) {
  int tickCount = 0;
  while(tickCount < (numTurns * numWindows * 2)) {
    counter.input(digitalRead(sensorPin));
    if (counter.changed()) {
      tickCount++;
    }
    delay(1 / sampleRate * 1000);
  }
}

void IRSensor::waitForTicks(float numTicks) {
  int tickCount = 0;
  while(tickCount < numTicks) {
    counter.input(digitalRead(sensorPin));
    if (counter.changed()) {
      tickCount++;
    }
    Serial.println(tickCount);
    delay(1 / sampleRate * 1000);
  }
}

void IRSensor::sample() {
  counter.input(digitalRead(sensorPin));
  if (counter.changed()) {
    this->tickCount++;
  }
  if (tickCount >= numWindows * 2) {
    turnCount++;
  }
}

int IRSensor::getTurnCount() {
  return this->turnCount;
}

int IRSensor::getTickCount() {
  return this->tickCount;
}
