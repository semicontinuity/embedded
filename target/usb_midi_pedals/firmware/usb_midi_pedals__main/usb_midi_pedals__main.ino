// Firmware for USB MIDI Pedals adapter.
// 2 Pedals report their state in MIDI CC messages
// - Pedal 1 (CC 64: damper)
// - Pedal 2 (CC 65: portamento)
// CC Values: 127 for pedal pressed, 0 for depressed

// Install DigiMIDI library from https://github.com/heartscrytech/DigisparkMIDI
#include <DigiMIDI.h>


DigiMIDIDevice midi;

#define DEBOUNCE_DELAY 50
#define PEDAL_1_PIN 0  // phys pin 5 (PB0) of ATTINY85
#define PEDAL_2_PIN 2  // phys pin 7 (PB2) of ATTINY85

int pedal1DebouncedState = HIGH;
unsigned long pedal1ReadingTime = 0;

int pedal2DebouncedState = HIGH;
unsigned long pedal2ReadingTime = 0;


void setup() {
  debugSetup();
  debugBlink(3);
  
  pinMode(PEDAL_1_PIN, INPUT_PULLUP);
  pinMode(PEDAL_2_PIN, INPUT_PULLUP);
}


void send_report(int cc, int pin_state) {
  midi.sendControlChange(cc, pin_state == LOW ? 127 : 0);
}


void loop() {
  midi.update();
 
  int pedal1Reading = digitalRead(PEDAL_1_PIN);
  if (pedal1Reading != pedal1DebouncedState) {
      pedal1DebouncedState = pedal1Reading;
      send_report(64, pedal1DebouncedState);
      delay(40); // poor man's debouncing
  }

  
  int pedal2Reading = digitalRead(PEDAL_2_PIN);
  if (pedal2Reading != pedal2DebouncedState) {
      pedal2DebouncedState = pedal2Reading;
      send_report(65, pedal2DebouncedState);
      delay(40); // poor man's debouncing
  }
}
