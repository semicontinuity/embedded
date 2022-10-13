#include <DigiMouse.h>

void setup()
{
  pinMode(1, OUTPUT);
  DigiMouse.begin();
  randomSeed(analogRead(0));
}


void loop() {
  unsigned int random_x = 1 - random(3);
  DigiMouse.moveX(random_x);

  digitalWrite(1, HIGH);
  DigiMouse.delay(20);
  digitalWrite(1, LOW);

  DigiMouse.delay(30000);
}
