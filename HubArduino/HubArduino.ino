#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

// hardware serial: does not need the RTS/CTS pins.
// Adafruit_BluefruitLE_UART ble(Serial1, BLUEFRUIT_UART_MODE_PIN);

void setup(void) {
  Serial.begin(115200);
  if (!ble.begin()) Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  if (FACTORYRESET_ENABLE && !ble.factoryReset()) Serial.println(F("Couldn't factory reset"));
  ble.echo(false);
  ble.info();
  while (!ble.isConnected()) delay(500);
}

void loop(void) {
  char inputs[BUFSIZE+1]; // Check for user input
  if (getUserInput(inputs, BUFSIZE)) {
    // Send characters to Bluefruit
    Serial.print("[Send] ");
    Serial.println(inputs);
    ble.print("AT+BLEUARTTX=");
    ble.println(inputs);
    if (!ble.waitForOK()) Serial.println(F("Failed to send"));
  }
  // Check for incoming characters from Bluefruit
  ble.println("AT+BLEUARTRX");
  ble.readline();
  if (strcmp(ble.buffer, "OK") == 0)  return;
  Serial.print(F("[Recv] ")); Serial.println(ble.buffer);
  ble.waitForOK();
}

bool getUserInput(char buffer[], uint8_t maxSize) {
  TimeoutTimer timeout(100);
  memset(buffer, 0, maxSize);
  while((!Serial.available()) && !timeout.expired()) delay(1);
  if (timeout.expired()) return false;
  delay(2);
  uint8_t count=0;
  do {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && (Serial.available()) );
  return true;
}
