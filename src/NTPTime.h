#ifndef NTPTime_H
#define NTPTime_H

#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Time.h>

void setupTime();
void forceUpdate(void);
String getTime();
String getDate();

#endif
