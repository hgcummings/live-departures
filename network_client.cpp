#include <ESP8266WiFi.h>

#include "network.h"

WiFiClient network_client(void (*spinner)()) {
  Serial.printf("Connecting to %s", ssid);
  WiFi.config(local_ip, gateway_ip, subnet_mask);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    spinner();
  }
 
  Serial.println("");
  Serial.println("WiFi connected");

  WiFiClient client;
  client.setNoDelay(true);
  return client;
}
