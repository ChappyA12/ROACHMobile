#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX

void setup()  {
   Serial.begin(9600);
   xbee.begin(9600);
}

void loop()  {
  if(xbee.available()) Serial.println(xbee.read());
  delay(50);
}
