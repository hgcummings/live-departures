#include <ESP8266WiFi.h>

#include "network.h"

WiFiClient network_client() {
  Serial.println();
  Serial.println();
  Serial.printf("Connecting to %s", ssid);
  WiFi.config(client_ip, dns_ip, gateway_ip);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");

  WiFiClient client;
  client.setNoDelay(true);
  return client;
}
