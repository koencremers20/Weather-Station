#include "Display.h"

char buffer[100] = {0};
int currentPage = 0;
// Declare a button object [page id:0,component id:1, component name: "b0"]
NexHotspot b0 = NexHotspot(0, 5, "b0");
NexHotspot b1 = NexHotspot(1, 5, "b1");

NexNumber tempText = NexNumber(0, 6, "temperature");
NexNumber humText = NexNumber(0, 8, "humidity");
NexNumber windSpeedText = NexNumber(0, 7, "windspeed");
NexText wifiText = NexText(0, 2, "wifi");
NexText dateText = NexText(0,4,"date");
NexText timeText = NexText(0,3,"time");
NexText updateText = NexText(0, 13, "update");

NexPage weatherPage = NexPage(0,0,"page0");
NexPage ledPage = NexPage(1,0,"page1");

NexSlider redSlider = NexSlider(1,2,"h0");
NexSlider greenSlider = NexSlider(1,3,"h1");
NexSlider blueSlider = NexSlider(1,4,"h2");

int previousMillis = 0;
int interval = 60000;
boolean test = false;

WeatherObject object;

NexTouch *nex_listen_list[] = {
  &b0,
  &b1,
  &redSlider,
  &greenSlider,
  &blueSlider,
  NULL
};
void displayOnScreen(WeatherObject x)
{
  windSpeedText.setValue(x.windspeed);
  windSpeedText.setValue(x.windspeed);
  tempText.setValue(x.temperature);
  humText.setValue(x.humidity);
  updateText.setText(getTime().c_str());
  object = x;
}

void displayOnScreen(IPAddress x)
{
  String ipStr = String(x[0])+"."+String(x[1])+"."+String(x[2])+"."+String(x[3]);
  wifiText.setText(ipStr.c_str());
}

void displayOnScreen(String x, String y)
{
  dateText.setText(x.c_str());
  timeText.setText(y.c_str());
}

void setupDisplay()
{
  nexInit();
  //Register the pop event callback function of the current button component
  b0.attachPop(b0PopCallback, &b0);
  b1.attachPop(b1PopCallback, &b1);
  redSlider.attachPop(redSliderPopCallback);
  greenSlider.attachPop(greenSliderPopCallback);
  blueSlider.attachPop(blueSliderPopCallback);
  dbSerialPrintln("setup done");
}

// Button component push callback function
void b0PopCallback(void *ptr) {
  // client.publish("office/workbench/buttonState", "true");
  switch(currentPage)
  {
    case 0:
      ledPage.show();
      currentPage = 1;
      break;
    case 1:
      weatherPage.show();
      displayOnScreen(getDate(), getTime());
      displayOnScreen(getDate(), getTime());
      displayOnScreen(object);
      delay(500);
      displayOnScreen(WiFi.localIP());
      currentPage = 0;
      break;
  }
}

void b1PopCallback(void *ptr) {
  // client.publish("office/workbench/buttonState", "true");
  switch(currentPage)
  {
    case 0:
      ledPage.show();
      currentPage = 1;
      break;
    case 1:
      weatherPage.show();
      displayOnScreen(getDate(), getTime());
      displayOnScreen(getDate(), getTime());
      displayOnScreen(object);
      delay(500);
      displayOnScreen(WiFi.localIP());
      currentPage = 0;
      break;
  }
}

void redSliderPopCallback(void *ptr)
{
  uint32_t x = 0;
  redSlider.getValue(&x);
  adjustRed(x);
  ledPage.show();
}

void greenSliderPopCallback(void *ptr)
{
  uint32_t x = 0;
  greenSlider.getValue(&x);
  adjustGreen(x);
  ledPage.show();
}

void blueSliderPopCallback(void *ptr)
{
  uint32_t x = 0;
  blueSlider.getValue(&x);
  adjustBlue(x);
  ledPage.show();
}

void displayLoop()
{
  if(!test)
  {
    displayOnScreen(getDate(), getTime());
    displayOnScreen(getDate(), getTime());
    delay(500);
    displayOnScreen(WiFi.localIP());
    test = true;
  }
  if(currentPage == 0)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
      previousMillis = currentMillis;
      displayOnScreen(getDate(), getTime());
    }
  }
  nexLoop(nex_listen_list);
}
