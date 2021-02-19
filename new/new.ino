// #include "nacc.h"

// void setup() {
//   Serial.begin(19200);
//   initializeMPU();
// }
// void loop() {
//   readMPU();
//   Serial.print("Ax: "); Serial.print(AX);
//   Serial.print(" Ay: "); Serial.print(AY);
//   Serial.print(" Az: "); Serial.print(AZ);
//   Serial.print(" T: "); Serial.print(T);
//   Serial.print(" Gx: "); Serial.print(GX);
//   Serial.print(" Gy: "); Serial.print(GY);
//   Serial.print(" Gz: "); Serial.println(GZ);
// }


#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(A0, A1); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
