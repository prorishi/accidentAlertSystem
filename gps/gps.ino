#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include<EEPROM.h>

TinyGPSPlus gps;
SoftwareSerial softSerial(4, 3);

double latitude=0.000000f;
  double longitude=0.000000f;
  int date;
  int month;
  int year;
  int hour;
  int minute;
  int second;
  

struct data {
  double latitude;
  double longitude;
  int date;
  int month;
  int year;
  int hour;
  int minute;
  int second;  
};

void setup() {
  Serial.begin(9600);
  softSerial.begin(9600);
  Serial.println("Initilizing...\n");
}

void loop() {
  while (softSerial.available() > 0)
    if (gps.encode(softSerial.read())) {
      if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()){
        latitude = gps.location.lat();
        longitude  =gps.location.lng();
      }
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
      }
        hour= gps.time.hour();
        minute=gps.time.minute();
        second= gps.time.second();
      }
      if(millis()>60000){
        data ndata = {
          latitude,
          longitude,
          date,
          month,
          year,
          hour,
          minute,
          second
        };
        EEPROM.put(0, ndata);
      }
    }
    
  if (millis() > 60000 && gps.charsProcessed() < 10) {
    char fdata[8] = "failed";
    EEPROM.put(0, fdata);
    while(true);
  }
}
