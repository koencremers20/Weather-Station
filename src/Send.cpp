#include "Send.h"

String sendToServer(WiFiClient client, IPAddress server, int serverPort, int temp, int humidity, int windForce)
{
//  Serial.println(windForce);
  if(!client.connect(server, serverPort)) {return "Cant connect";}   // Connection to the server

  //client.connect(server, 80);
  client.print("Temp=");
  client.print(temp);
  client.print("&Hum=");
  client.print(humidity);
  client.print("&Windforce=");
  client.print(20.2);
  client.println("\r");  // sends the message to the server
  client.flush();
  return "from server: " + client.readStringUntil('\r');   // receives the answer from the sever
}
