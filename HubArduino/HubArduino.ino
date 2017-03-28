#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX
int i = 0;

void setup()  {
   Serial.begin(9600);
   xbee.begin(9600);
}

void loop()  {
  xbee.print(i);
  i = (i + 1) % 50;
  delay(50);
}
