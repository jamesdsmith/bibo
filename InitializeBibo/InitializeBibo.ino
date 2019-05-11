#include "Statemachine.h"
#include "IRSensor.h"
#include "MotorDriver.h"

#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>

const int PIN_1 = 5;
const int PIN_2 = 6;
const int SENSOR_PIN = 9;
const int DIRECTION_PIN = A1;

// Pulse Sensor Setup
const int OUTPUT_TYPE = SERIAL_PLOTTER;
const int PULSE_INPUT = A2;
const int PULSE_BLINK = 13;
const int PULSE_FADE = 5;
const int THRESHOLD = 550;
const int BPM_THRESHOLD = 100;
const int TOTAL_TURNS = 2000;

byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

PulseSensorPlayground pulseSensor;
IRSensor ir(SENSOR_PIN);
MotorDriver motor(PIN_1, PIN_2);

bool motorActive = true;

void motorIn() {
  motor.CCW();
  ir.waitForTicks(TOTAL_TURNS);
  motor.Stop();
}

void motorOut() {
  motor.CW();
  ir.waitForTicks(TOTAL_TURNS);
  motor.Stop();
}

void setup() {
  Serial.begin(115200);
//  motorIn();

//  motorOut();
//  motor.CCW();
//  ir.waitForTicks(200);
//  motor.Stop();
//  motorIn();
motorOut();

  motorIn();
//  motor.CCW();
////  2600
//  ir.waitForTicks(2600);
//  motor.Stop();
////  ir.waitForTurns(1);
////  motor.Stop();
//  //  motor.CW();
//  motorOut();
//  motorIn();
}

void loop() {
//  motorIn();
//  motorOut();
//  motorIn();
  
     
//    ir.sample();
//    Serial.println(ir.getTickCount());
////    if (ir.getTurnCount() > 1) {
////      motor.Stop();
////      motorActive = false;
////    }
//
//    delay(10);

}
