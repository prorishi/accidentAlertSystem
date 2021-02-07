#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial softSerial(4, 5);

String position[2];
// int year , month , date, hour , minute , second;

void initializeGPS() {
    softSerial.begin(9600);
}

void readGPS() {
    if (softSerial.available() > 0) {
        if (gps.encode(softSerial.read())) {
            if (gps.location.isValid()) {
                position[0] = String(gps.location.lat() , 6);
                position[1] = String(gps.location.lng() , 6);
            }
        }
    }
}