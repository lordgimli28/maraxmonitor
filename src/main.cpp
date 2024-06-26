#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Timer.h>
#include <SoftwareSerial.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "global_defines.h"
#include "mara_input.h"
#include "disp.h"
#include "webserver.h"
#include "mqtt.h"

void updateLoop(){
  tempCoffee = parseCharToTemp(14, receivedChars);
  tempSteam = parseCharToTemp(6, receivedChars);
  updateDisplay();
  loopWebServer();
}

void setup() {
  initWiFi();
  setup_mqtt();
  setup_input();

  t.every(100, updateLoop);

  memset(receivedChars, 0, numChars );

  setup_display();
  
  mySerial.write(0x11);

  handleWebServer();
}

void loop() {
  t.update();
  detectChanges();
  getMachineInput();
  update_mqtt();
}