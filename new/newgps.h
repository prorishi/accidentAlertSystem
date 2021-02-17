#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// rx to 3, tx to 4

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3);

String location[2], date[3], time[3];
int dd, mm, yy, h, m, s;

void initializeGPS() {
    gpsSerial.begin(115200);
}

void readGPS() {
    if (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isValid()) {
                location[0] = String(gps.location.lat() , 6),
                location[1] = String(gps.location.lng() , 6);
            }
            if (gps.date.isValid()) {
                dd = gps.date.day(),
                mm = gps.date.month(),
                yy = gps.date.year();
                date[0] = lt10(dd) + String(dd),
                date[1] = lt10(mm) + String(mm),
                date[2] = lt10(yy) + String(yy);
            }
            if (gps.time.isValid()) {
                h = gps.time.hour() + 5,
                m = gps.time.minute() + 30,
                s = gps.time.second();
                h = h > 23 ? h - 24 : h;
                if (m > 59) {
                    m -= 60;
                    h += 1;
                }
                time[0] = lt10(h) + String(h),
                time[1] = lt10(m) + String(m),
                time[2] = lt10(s) + String(s);
            }
        }
    }
}

void lt10 (int number) {
    return number < 10 ? '0' : ''
}