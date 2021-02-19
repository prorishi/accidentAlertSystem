// TX is digital pin 10 
// RX is digital pin 11 

#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(A0, A1); 

void initializeGSM() {
    gsmSerial.begin(9600);
}
//
//void call(char[] num) {
//    gsmSerial.println("ATD" + num + ';'); 
//}
