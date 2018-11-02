#include "DHTSensor.h"

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
  dht.begin();
}

int getHumidity() {
  float h = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  if (isnan(h) || h > 100) {
    return 0;
  }
  return (int) round(h);
}

int getTemperature() {
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  if (isnan(t) || t > 50) {
    return 0;
  }
  return (int) round(t);
}
