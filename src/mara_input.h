#ifndef MARA_INPUT_H
#define MARA_INPUT_H


  void getMachineInput() 
  {
    while (mySerial.available() ) 
    {
      serialUpdateMillis = millis();
      rc = mySerial.read();

      if (rc != endMarker) 
      {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } 
      else 
      {
        receivedChars[ndx] = '\0';
        ndx = 0;
        Serial.println(receivedChars);
      }
    }
    if (millis() - serialUpdateMillis > 5000) 
    {
      serialUpdateMillis = millis();
      memset(receivedChars, 0, numChars);
      Serial.println("Request serial update");
      mySerial.write(0x11);
    }
}

void detectChanges() 
{
  pumpInValue = 1;
  Serial.println(receivedChars);
  if (String(receivedChars[25]) == "1") 
  {
    pumpInValue = 0;
    Serial.println("pump on");
  }
  else
  {
    pumpInValue = 1;
    Serial.println("pump off");
  }
  
  if (!timerStarted && !pumpInValue) 
  {
    timerStartMillis = millis();
    timerStarted = true;
    displayOn = true;
    Serial.println("Start pump");
  }
  if (timerStarted && pumpInValue) 
  {
    if (timerStopMillis == 0) 
    {
      timerStopMillis = millis();
    }
    if (millis() - timerStopMillis > 500) 
    {
      timerStarted = false;
      timerStopMillis = 0;
      timerDisplayOffMillis = millis();
      display.invertDisplay(false);
      Serial.println("Stop pump");
    }
  } 
  else 
  {
    timerStopMillis = 0;
  }
  if (!timerStarted && displayOn && timerDisplayOffMillis >= 0 && (millis() - timerDisplayOffMillis > 1000 * 60 * 60)) 
  {
    timerDisplayOffMillis = 0;
    timerCount = 0;
    prevTimerCount = 0;
    displayOn = false;
    Serial.println("Sleep");
  }
}

String getTimer() 
{
  char outMin[2];
  if (timerStarted) 
  {
    timerCount = (millis() - timerStartMillis ) / 1000;
    if (timerCount > 15) 
    {
      prevTimerCount = timerCount;
    }
  } 
  else 
  {
    timerCount = prevTimerCount;
  }
  if (timerCount > 99) 
  {
    return "99";
  }
  sprintf( outMin, "%02u", timerCount);
  return outMin;
}

void setup_input(void)
{
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}
#endif