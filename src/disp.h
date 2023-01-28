#ifndef DISP_H
#define DISP_H

void updateDisplay() 
{
  display.clearDisplay();
  if (displayOn) 
  {
    if (timerStarted) {
      display.setTextSize(7);
      display.setCursor(25, 8);
      display.print(getTimer());
    } 
    else 
    {
      // draw line
      display.drawLine(74, 0, 74, 63, SSD1306_WHITE);
      // draw time seconds
      display.setTextSize(4);
      display.setCursor(display.width() / 2 - 1 + 17, 20);
      display.print(getTimer());
      // draw machine state C/S
      if (receivedChars[0] ) 
      {
        display.setTextSize(2);
        display.setCursor(1, 1);
        if (String(receivedChars[0]) == "C") 
        {
          display.print("C");
        } 
        else if (String(receivedChars[0]) == "V") 
        {
          display.print("S");
        } else 
        {
          display.print("X");
        }
      }
      if (String(receivedChars).substring(18, 22) == "0000") 
      {
        // not in boost heating mode
        // draw fill circle if heating on
        if (String(receivedChars[23]) == "1") 
        {
          display.fillCircle(45, 7, 6, SSD1306_WHITE);
        }
        // draw empty circle if heating off
        if (String(receivedChars[23]) == "0") 
        {
          display.drawCircle(45, 7, 6, SSD1306_WHITE);
        }
      } 
      else 
      {
        // in boost heating mode
        // draw fill rectangle if heating on
        if (String(receivedChars[23]) == "1") 
        {
          display.fillRect(39, 1, 12, 12, SSD1306_WHITE);
        }
        // draw empty rectangle if heating off
        if (String(receivedChars[23]) == "0") 
        {
          display.drawRect(39, 1, 12, 12, SSD1306_WHITE);
        }
      }
      // draw temperature
      if (receivedChars[14] && receivedChars[15] && receivedChars[16]) 
      {
        display.setTextSize(3);
        display.setCursor(1, 20);
        if (String(receivedChars[14]) != "0") 
        {
          display.print(String(receivedChars[14]));
        }
        display.print(String(receivedChars[15]));
        display.print(String(receivedChars[16]));
        display.print((char)247);
        if (String(receivedChars[14]) == "0") 
        {
          display.print("C");
        }
      }
      // draw steam temperature
      if (receivedChars[6] && receivedChars[7] && receivedChars[8]) 
      {
        display.setTextSize(2);
        display.setCursor(1, 48);
        if (String(receivedChars[6]) != "0") 
        {
          display.print(String(receivedChars[6]));
        }
        display.print(String(receivedChars[7]));
        display.print(String(receivedChars[8]));
        display.print((char)247);
        display.print("C");
      }
    }
  }
  display.display();
}

void setup_display(void)
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
}
#endif