#include "Json.h"

int sendPackage(WeatherObject x) {
  StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
  JsonObject& JSONencoder = JSONbuffer.createObject();

  JSONencoder["deviceId"] = idDevice;
  JSONencoder["temperatureC"] = x.temperature;
  JSONencoder["humidity"] = x.humidity;
  JSONencoder["windspeed"] = x.windspeed;

  //JsonArray& additional = JSONencoder.createNestedArray("Overige");
  //JsonObject& additional1 = additional.createNestedObject();
  //additional1["naam"] = "woonkamertemperatuur";
  //additional1["waarde"] = temp;

  //JsonObject& additional2 = additional.createNestedObject();
  //additional2["naam"] = "windrichting";
  //additional2["waarde"] = 180;

  char JSONmessageBuffer[300];
  JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println(JSONmessageBuffer);

  HTTPClient http;    //Declare object of class HTTPClient

  http.begin(ipClassServer);      //Specify request destination
  http.addHeader("Content-Type", "application/json");  //Specify content-type header

  int httpCode = http.POST(JSONmessageBuffer);   //Send the request
  String payload = http.getString();                                        //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload

  http.end();  //Close connection
  return httpCode;
}
