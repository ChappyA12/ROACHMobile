#include <SoftwareSerial.h>

SoftwareSerial xbeeIn =  SoftwareSerial(2, 3);
//SoftwareSerial xbeeOut =  SoftwareSerial(5, 4);

void setup()  {
   Serial.begin(9600);
   xbeeIn.begin(9600);
   //xbeeOut.begin(9600);
}

void loop()  {
  //xbeeOut.write(99);
  Serial.println(xbeeIn.available());
  if(xbeeIn.available()) Serial.println(xbeeIn.read());
  delay(200);
}
