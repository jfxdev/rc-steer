#include "Steer.h"

#define SERVO_PIN  6
#define VRX        A5
#define SW         2
#define BUZZER_PIN 4

Steer steer(SERVO_PIN);

void setup() {
  steer.Setup(BUZZER_PIN, SW, 2000);
}

void loop() {
  steer.Read(analogRead(VRX));
  steer.Set();
}
