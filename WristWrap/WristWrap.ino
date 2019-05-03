#include "Statemachine.h"
#include "IRSensor.h"
#include "MotorDriver.h"

#define PIN_1 5
#define PIN_2 6
#define SENSOR_PIN 10
#define DIRECTION_PIN A1

IRSensor ir(SENSOR_PIN);
MotorDriver motor(PIN_1, PIN_2);

bool motorActive = true;

void setup() {
  Serial.begin(9600);
  
//  motor.CCW();
//  ir.waitForTurns(1);
//  motor.Stop();
  motor.CW();
}

void loop() {
  ir.sample();
  if (ir.getTurnCount() > 1) {
    motor.Stop();
    motorActive = false;
  }

  if (motorActive) {
    if (analogRead(DIRECTION_PIN) > 512) {
      motor.CW();
    } else {
      motor.CCW();
    }
  }
  delay(10);
}
