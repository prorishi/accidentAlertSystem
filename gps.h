#include <SoftwareSerial.h>

SoftwareSerial ss(A4, A5);

void initiializeGPS()
{
    ss.begin(9600);
}

void getLocation()
{
    while (ss.available() > 0)
    {
        byte gpsData = ss.read();
        Serial.write(gpsData);
    }
}