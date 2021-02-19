#include "mpu.h"

// MPU mpu;
void setup() {
  Serial.begin(19200);
  // mpu.initialize();
  initializeMPU();
}
void loop() {
  // mpu.read();
  readMPU();
  Serial.print("Ax: "); Serial.print(AX);
  Serial.print(" Ay: "); Serial.print(AY);
  Serial.print(" Az: "); Serial.print(AZ);
  Serial.print(" T: "); Serial.print(T);
  Serial.print(" Gx: "); Serial.print(GX);
  Serial.print(" Gy: "); Serial.print(GY);
  Serial.print(" Gz: "); Serial.println(GZ);
}