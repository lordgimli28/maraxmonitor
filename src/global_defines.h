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
    int pumpInValue = 0;

    const byte numChars = 32;
    char receivedChars[numChars];
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
#endif