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

byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

PulseSensorPlayground pulseSensor;
IRSensor ir(SENSOR_PIN);
MotorDriver motor(PIN_1, PIN_2);

bool motorActive = true;

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
  
//  motor.CCW();
//  ir.waitForTurns(1);
//  motor.Stop();
  //  motor.CW();
}

void loop() {
  //  ir.sample();
  //  if (ir.getTurnCount() > 1) {
  //    motor.Stop();
  //    motorActive = false;
  //  }
  //
  //  if (motorActive) {
  //    if (analogRead(DIRECTION_PIN) > 512) {
  //      motor.CW();
  //    } else {
  //      motor.CCW();
  //    }
  //  }
  //  delay(10);

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
      motor.CCW();
    } else {
      motor.Stop();
    }
  }
}
