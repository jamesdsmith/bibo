#include "Statemachine.h"
#include "IRSensor.h"
#include "MotorDriver.h"

#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>

const int PIN_1 = 5;
const int PIN_2 = 6;
const int SENSOR_PIN = 9;
const int DIRECTION_PIN = A1;

const int TOTAL_TURNS = 2000;
const int LOADED_TURNS = 200;

IRSensor ir(SENSOR_PIN);
MotorDriver motor(PIN_1, PIN_2);

bool motorActive = true;

void motorIn() {
  motor.CCW();
  ir.waitForTicks(TOTAL_TURNS);
  motor.Stop();
}

void setup() {
  Serial.begin(115200);
  motor.CCW();
  ir.waitForTicks(LOADED_TURNS);
  motor.Stop();
  
  motorIn();
}

void loop() {
}
