#include <ESP8266WiFi.h>

#include "network.h"
#include "display.h"
#include "data.h"
#include "state.h"

int bus_count = sizeof(buses) / sizeof(buses[0]);
WiFiClient client;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  display_init();
  display_loading(loading_icon);

  client = network_client();
  uint8_t i = state_get() % bus_count;
  state_set((i + 1) % bus_count);

  show_arrivals(i);

  delay(8000);
  display_clear();
  state_set(i);
  ESP.deepSleep(0);
}

void loop() {
}

void show_arrivals(uint8_t i) {
  Serial.print("Connecting to ");
  Serial.print(host_ip);
  Serial.printf(":%d\n", host_port);
  if (!client.connect(host_ip, host_port)) {
    Serial.println("connection failed");
    return;
  }
  
  Serial.printf("Requesting arrivals for bus %d\n", buses[i].number);
  client.write(buses[i].number);

  int next;
  int found = 0;

  Serial.print("Awaiting response from server");
  while(client.connected() && !client.available()) {
    delay(10);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("Displaying arrivals");
  while(client.connected() && can_display_arrival()){
    next = client.read();
    
    Serial.printf("- Arrival in %d deciseconds\n", next);

    int minutes = next / 6;
    if (minutes < 3) {
      continue; 
    }

    if (found == 0) {
      display_arrivals_begin(buses[i].icon);
    }

    found++;

    display_arrival(minutes);
  }
  display_arrivals_end();
  
  Serial.println("Done");
}

