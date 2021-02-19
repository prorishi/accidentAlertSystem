#include <SoftwareSerial.h>
#include <Wire.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3);
SoftwareSerial gsmSerial(10, 11); 

String location, date, time;
int h, m;

uint8_t mpuRegisters[] = { 0x19, 0x6B, 0X6C, 0X1A, 0X1B, 0X1C, 0X23, 0X38, 0X68, 0X6A };
uint8_t mpuRegisterData[] = { 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };

double AX, AY, AZ, T, GX, GY, GZ;

void initializeMPU() {
    Wire.begin();
    delay(150);
    for (int i = 0; i < 10; i++) {
        Wire.beginTransmission(0x68);
        Wire.write(mpuRegisters[i]);
        Wire.write(mpuRegisterData[i]);
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

void initializeGPS() {
    gpsSerial.begin(9600);
}

void readGPS() {
    if (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isValid()) {
                location += String(gps.location.lat() , 6);
                location += "N, ";
                location += String(gps.location.lng() , 6);
                location += "E";
            }
            if (gps.date.isValid()) {
                date +=String(gps.date.day());
                date += "/";
                date += String(gps.date.month());
                date += "/";
                date += String(gps.date.year());
            }
            if (gps.time.isValid()) {
                h = gps.time.hour() + 5,
                m = gps.time.minute() + 30;
                if (h > 23) h -= 24;
                if (m > 59) {
                    m -= 60;
                    h += 1;
                }
                time += String(h);
                time += ":";
                time += String(m);
                time += ":";
                time +=  String(gps.time.second());
            }
        }
    }
}

void initializeGSM() {
    gsmSerial.begin(9600);
}

void sendSMS(String phn) {
    gsmSerial.println("AT+CMGF=1"); 
    gsmSerial.println("AT+CMGS=\"+91" + phn + "\"");
    gsmSerial.print("helo"); 
    gsmSerial.write(26);
}