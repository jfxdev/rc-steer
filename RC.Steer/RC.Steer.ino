#include "Steer.h"

#define SERVO_PIN  6
#define VRX        A5
#define SW         2
#define BUZZER_PIN 4
#define HORN_FREQUENCY 3000

Steer steer(SERVO_PIN, 0, 1023, 10, 170);

void setup() {
  steer.Setup(BUZZER_PIN, SW, HORN_FREQUENCY);
}

void loop() {
  steer.Read(analogRead(VRX));
  steer.Set();
}
