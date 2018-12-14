#include "ESP8266WiFi.h"
#include <SoftwareSerial.h>
#include <PubSubClient.h>

#define MASTER    'M'
#define PIN_LED   13
#define TX        D6
#define RX        D5
#define RX_TX     D2

//SoftwareSerial Ser1(RX, TX);
SoftwareSerial Ser1(RX, TX, false, 256);

void setup() {
  Serial.begin(9600);
  Ser1.begin(9600);
  pinMode (RX_TX, OUTPUT);
  digitalWrite(RX_TX, LOW); 
}

void loop() 
{
  serial_handle(); 
  software_serial_handle();
  wifi_handle();
}
