#include <SoftwareSerial.h>
#include <Wire.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3);
SoftwareSerial gsmSerial(10, 11); 

uint8_t mpuRegisters[] = { 0x19, 0x6B, 0X6C, 0X1A, 0X1B, 0X1C, 0X23, 0X38, 0X68, 0X6A };
uint8_t mpuRegisterData[] = { 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };

double AX, AY, AZ, T, GX, GY, GZ;

int hour , minute;
String dt = "", t = "", pos = "";
// int pm;

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
    while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isValid()) {
                pos = String(gps.location.lat()); 
                pos += ", ";
                pos += String(gps.location.lng()); 
            }
            if (gps.date.isValid()) {
                dt = String(gps.date.day());
                dt += " / ";
                dt += String(gps.date.month());
                dt += " / ";
                dt += String(gps.date.year()); 
            }
            if (gps.time.isValid()) {
                hour = gps.time.hour();
                minute = gps.time.minute();
                minute += 30; 
                if (minute > 59) {
                    minute -= 60;
                    hour += 1;
                }
                hour += 5;
                if (hour > 23) hour -= 24;  
                // if (hour >= 12)  
                // pm = 1;
                // else
                // pm = 0;
                // hour = hour % 12;
                if (hour < 10)
                t = '0';
                t += String(hour); 
                t += " : ";
                if (minute < 10)
                t += '0';
                t += String(minute); 
                t += " : ";
                if (second < 10)
                t += '0';
                t += String(gps.time.second());
                // if (pm == 1)
                // time_str += " PM ";
                // else
                // time_str += " AM ";
            }
        }
    }
    
}

void initializeGSM() {
    gsmSerial.begin(9600);
}

void sendSMS(String phn) {
    gsmSerial.print("AT+CMGF=1\r\n"); 
    gsmSerial.print("AT+CMGS=\"+91" + phn + "\"\r\n");
    gsmSerial.print("helo"); 
    gsmSerial.write(26);
    gsmSerial.print("AT+CMGF=1\r\n"); 
}

void call(String phn) {
    gsmSerial.print("ATD+91" + phn + "\r\n");
}

bool recvCall() {
    char inc[5] = "";
    while (gsmSerial.available() > 0) {
        inc += (char) gsmSerial.read();
    }
    if (strcmp(inc, "RING") == 0) {
        return 1;
    } else {
        return 0;
    }
}