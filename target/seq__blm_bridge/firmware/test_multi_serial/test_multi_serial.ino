#include <Arduino.h>

// uses Arduino config with just 2 variants for F103C8
// upload method ST-Link

void setup() {
    pinMode(PC13, OUTPUT);

    Serial3.begin(38400);
    Serial1.begin(38400);
    Serial2.begin(38400);

}


void loop() {
    digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                // wait for a second

    Serial3.write('A');     // on PB10 "TX3"
    Serial1.write('B');     // on PA9 "TX1"
    Serial2.write('C');     // on PA2 "TX2"

    digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                // wait for a second

    Serial3.write('-');
    Serial1.write('-');
    Serial2.write('-');
}
