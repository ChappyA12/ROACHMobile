#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

SoftwareSerial bleSerial = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bleSerial, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

void setup() {
  Serial.begin(9600);
  if (!ble.begin()) Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  if (FACTORYRESET_ENABLE && !ble.factoryReset()) Serial.println(F("Couldn't factory reset"));
  ble.echo(false);
  ble.info();
  //while (!ble.isConnected()) delay(500); //dont continue to loop until connected to phone
}

void loop() {
  String s = "";
  if (Serial.available() > 0)
      s = Serial.read();
  if (s.length() != 0) {
    String input = Serial.readString();
    //-------------------------------SEND-------------------------------
    Serial.print("[Send] ");
    Serial.println(s);
    ble.print("AT+BLEUARTTX=");
    ble.println(s);
    //if (!ble.waitForOK()) Serial.println(F("Failed to send"));
    //------------------------------------------------------------------
  }
    //-----------------------------RECIEVE------------------------------
    ble.println("AT+BLEUARTRX");
    ble.readline();
    if (strcmp(ble.buffer, "OK") != 0) {
      String s = ble.buffer;
      Serial.println("[Recv] " + s);
      //ble.waitForOK();
    }
    //------------------------------------------------------------------
}
