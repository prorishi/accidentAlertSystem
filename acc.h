#include <Wire.h>
#include <MPU6050.h>

MPU6050 sensor;
int tilt[2];

void initializeAccelerometer() {
    while(!sensor.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G)) {}
}

int *readTilt() {
  Vector acceleration = sensor.readNormalizeAccel();
  tilt[0] = -(atan2(acceleration.XAxis, sqrt(acceleration.YAxis * acceleration.YAxis + acceleration.ZAxis * acceleration.ZAxis)) * 180.0) / M_PI;
  tilt[1] = (atan2(acceleration.YAxis, acceleration.ZAxis) * 180.0) / M_PI;
  return tilt;
}
