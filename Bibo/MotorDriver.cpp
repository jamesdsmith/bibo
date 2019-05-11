#include "Arduino.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(int pin1, int pin2) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  pinMode(this->pin1, OUTPUT);
  pinMode(this->pin2, OUTPUT);
}

void MotorDriver::CW() {
  digitalWrite(this->pin1, HIGH);
  digitalWrite(this->pin2, LOW);
}

void MotorDriver::CCW() {
  digitalWrite(this->pin1, LOW);
  digitalWrite(this->pin2, HIGH);
}

void MotorDriver::Stop() {
  digitalWrite(this->pin1, LOW);
  digitalWrite(this->pin2, LOW);
}

void MotorDriver::Brake() {
  digitalWrite(this->pin1, HIGH);
  digitalWrite(this->pin2, HIGH);
}
