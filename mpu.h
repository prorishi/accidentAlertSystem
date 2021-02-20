#include <Wire.h>

uint8_t registers[] = { 0x19, 0x6B, 0X6C, 0X1A, 0X1B, 0X1C, 0X23, 0X38, 0X68, 0X6A };
uint8_t d[] = { 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };

double AX, AY, AZ, T, GX, GY, GZ;

void initializeMPU() {
    Wire.begin();
    delay(150);
    for (int i = 0; i < 10; i++) {
        Wire.beginTransmission(0x68);
        Wire.write(registers[i]);
        Wire.write(d[i]);
        Wire.endTransmission();
        delay(10);
    }
}

void readMPU() {
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(0x68, (uint8_t)14);
    AX = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 1634,
    AY = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 1634,
    AZ = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 1634,
    T = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 340 + 36.53,
    GX = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 131,
    GY = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 131,
    GZ = (double) (((int16_t) Wire.read() << 8) | Wire.read()) / 131;
}