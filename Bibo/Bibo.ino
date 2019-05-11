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
const int TOTAL_TURNS = 2600;

byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

PulseSensorPlayground pulseSensor;
IRSensor ir(SENSOR_PIN);
MotorDriver motor(PIN_1, PIN_2);

bool motorActive = true;
bool motorIsIn = false;

void motorIn() {
  motorIsIn = true;
  motor.CCW();
  ir.waitForTicks(TOTAL_TURNS);
  motor.Stop();
}

void motorOut() {
  motorIsIn = false;
  motor.CW();
  ir.waitForTicks(TOTAL_TURNS);
  motor.Stop();
}

void setup() {
  Serial.begin(115200);

  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);

  if (!pulseSensor.begin()) {
    // Init failed. We should probably comment this out
    for(;;) {
      // Flash the led to show things didn't work.
      digitalWrite(PULSE_BLINK, LOW);
      delay(50);
      digitalWrite(PULSE_BLINK, HIGH);
      delay(50);
    }
  }
}

void loop() {
  if (pulseSensor.sawNewSample()) {
    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

      pulseSensor.outputSample();

      /*
         At about the beginning of every heartbeat,
         report the heart rate and inter-beat-interval.
      */
      if (pulseSensor.sawStartOfBeat()) {
        pulseSensor.outputBeat();
      }
    }
    
    int bpm = pulseSensor.getBeatsPerMinute(0);
    if (bpm > BPM_THRESHOLD) {
      if (motorIsIn) {
        motorOut();
      }
    } else {
      if (!motorIsIn) {
        motorIn();
      }
    }
  }
}
