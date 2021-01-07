#include "acc.h"

void setup() {
  Serial.begin(115200);
  initializeAccelerometer();
}

void loop() {
  int *tilt = readTilt();
    
  Serial.print(tilt[0]);
  Serial.print(" ");
  Serial.println(tilt[1]);
  delay(100);
}
