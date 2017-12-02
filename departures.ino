#include <ESP8266WiFi.h>

#include "network.h"
#include "display.h"
#include "data.h"

int bus_count = sizeof(buses) / sizeof(buses[0]);

void setup() {
  Serial.begin(9600);
  display_init();
  display_loading(loading_icon);

  WiFiClient client = network_client();
  if (!client.connect(host_ip, host_port)) {
    Serial.println("connection failed");
    return;
  }

  randomSeed(analogRead(0));
  int i = random(bus_count);
  Serial.printf("Requesting arrivals for bus %d\n", buses[i].number);
  client.write(buses[i].number);

  int next;
  int found = 0;

  Serial.println("Displaying arrivals");
  while(client.connected() && can_display_arrival()){
    next = client.read();

    if (next == -1) {
      continue; // No data received yet
    }
    
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

void loop() {
}
