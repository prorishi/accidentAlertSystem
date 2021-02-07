#include <Wire.h>

// scl to a4
// sda to a5


class MPU {
    private:
        const uint8_t registers[10] = {0x19, 0x6B, 0x6C0, 0x1A, 0x1B, 0x1C, 0x23, 0x38, 0x3B, 0x6A};
        const uint8_t data[10] = {0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00};
        
    public:
        double acceleration[3], tilt[3], temperature;

        void initialize() {
            Wire.begin();
            delay(150);
            for (int counter=0; counter<10; counter++) {
                Wire.beginTransmission(0x68);
                Wire.write(registers[counter]);
                Wire.write(data[counter]);
                Wire.endTransmission();
            }
        }
        void read(){
            Wire.beginTransmission(0x68);
            Wire.write(0x3B);
            Wire.endTransmission();
            Wire.requestFrom(0x68, uint8_t(14));
            acceleration[0] = double(int16_t(Wire.read() << 8) | Wire.read()) / 16384.0;
            acceleration[1] = double(int16_t(Wire.read() << 8) | Wire.read()) / 16384.0;
            acceleration[2] = double(int16_t(Wire.read() << 8) | Wire.read()) / 16384.0;
            tilt[0] = double(int16_t(Wire.read() << 8) | Wire.read()) / 131.0;
            tilt[1] = double(int16_t(Wire.read() << 8) | Wire.read()) / 131.0;
            tilt[2] = double(int16_t(Wire.read() << 8) | Wire.read()) / 131.0;
            temperature = (double(int16_t(Wire.read() << 8) | Wire.read()) / 340.0) + 36.53;
        }
};


double acceleration[3], tilt[3], temperature;

const uint8_t registers[10] = {0x19, 0x6B, 0x6C0, 0x1A, 0x1B, 0x1C, 0x23, 0x38, 0x3B, 0x6A};
const uint8_t data[10] = {0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00};

void initializeMPU() {
    Wire.begin();
    delay(150);
    for (int counter=0; counter<10; counter++) {
        Wire.beginTransmission(0x68);
        Wire.write(registers[counter]);
        Wire.write(data[counter]);
        Wire.endTransmission();
    }
}

void readMPU(){
    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(0x68, uint8_t(14));
    acceleration[0] = double(int16_t(Wire.read() << 8) | Wire.read()) / 16384.0;
    acceleration[1] = double(int16_t(Wire.read() << 8) | Wire.read()) / 16384.0;
    acceleration[2] = double(int16_t(Wire.read() << 8) | Wire.read()) / 16384.0;
    tilt[0] = double(int16_t(Wire.read() << 8) | Wire.read()) / 131.0;
    tilt[1] = double(int16_t(Wire.read() << 8) | Wire.read()) / 131.0;
    tilt[2] = double(int16_t(Wire.read() << 8) | Wire.read()) / 131.0;
    temperature = double(int16_t(Wire.read() << 8) | Wire.read()) / 340.0 + 36.53;
}
