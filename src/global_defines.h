#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

    Adafruit_SSD1306 display(128, 64, &Wire, -1);
    SoftwareSerial mySerial(14, 12);
    Timer t;

    // set to true/false when using another type of reed sensor
    bool reedOpenSensor = true;
    bool displayOn = true;
    int timerCount = 0;
    int prevTimerCount = 0;
    bool timerStarted = false;
    long timerStartMillis = 0;
    long timerStopMillis = 0;
    long timerDisplayOffMillis = 0;
    long serialUpdateMillis = 0;
    // 0 = pump on 1 = pump off
    int pumpInValue = 0;
    int tempSteam = 0;
    int tempCoffee = 0;

    const byte numChars = 32;
    char receivedChars[numChars];
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;

    const char* ssid     = "REPLACE_WITH_YOUR_SSID";
    const char* password = "REPLACE_WITH_YOUR_PASSWORD";

    // Create AsyncWebServer object on port 80
    AsyncWebServer server(80);

    // Create an Event Source on /events
    AsyncEventSource events("/events");


    // Set your Static IP address
    IPAddress local_IP(REPLACE);
    // Set your Gateway IP address
    IPAddress gateway(REPLACE);

    IPAddress subnet(REPLACE);
    IPAddress primaryDNS(REPLACE);   //optional
    IPAddress secondaryDNS(REPLACE); //optional

 
    // for mqtt

    WiFiClient wifiClient;

    int        mqtt_port     = 0;
    IPAddress mqtt_broker(REPLACE);

    const char* mqttUser = "";
    const char* mqttPassword = "";

    char config_buffer[512];
    DynamicJsonDocument config_doc(1024);

    const long interval = 10000;
    unsigned long previousMillis = 0;

    String mqtt_clientId = "MaraXClient" + String(random(0xffff), HEX);
    //mqtt_clientId += String(random(0xffff), HEX);

#endif