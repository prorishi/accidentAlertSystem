// TX is digital pin 10 
// RX is digital pin 11 

#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(10, 11); // RX, TX

void initializeGSM() {
    gsmSerial.begin(9600);
}

void Call(char[11] num) {
    gsmSerial.println("ATD" + num + ';'); 
}
