#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Timer.h>
#include <SoftwareSerial.h>
#include "global_defines.h"
#include "mara_input.h"
#include "disp.h"

void setup() {
  WiFi.mode(WIFI_OFF);

  setup_input();

  t.every(100, updateDisplay);

  memset(receivedChars, 0, numChars );

  setup_display();
  
  mySerial.write(0x11);
}

void loop() {
  t.update();
  detectChanges();
  getMachineInput();
}