// #include "acc.h"
#include"gps.h"

void setup() {
  Serial.begin(9600);
  // initializeAccelerometer();
  initiializeGPS();
}

void loop() {
  getLocation();
  delay(100);
  // int *tilt = readTilt();
    
  // Serial.print(tilt[0]);
  // Serial.print(" ");
  // Serial.println(tilt[1]);
  // delay(100);


}
