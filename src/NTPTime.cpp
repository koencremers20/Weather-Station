#include "NTPTime.h"

WiFiUDP ntpUDP;

int16_t utc = 1; //UTC -3:00 Brazil
uint32_t currentMillisTime = 0;
uint32_t previousMillisTime = 0;

NTPClient timeClient(ntpUDP, "nl.pool.ntp.org", utc*3600, 60000);

const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
const char * months[] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"} ;

void setupTime()
{
  timeClient.begin();
  timeClient.update();
}

void forceUpdate(void){
  timeClient.forceUpdate();
}

String getTime(){
  return timeClient.getFormattedTime();
}

String getDate(){
  char str[30];
  sprintf(str, "%s, %s %d, %d", days[weekday(timeClient.getEpochTime()) - 1], months[month(timeClient.getEpochTime()) - 1], day(timeClient.getEpochTime()), year(timeClient.getEpochTime()));
  return str;
}
