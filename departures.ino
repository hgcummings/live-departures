#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <ESP8266WiFi.h>

#include "network.h"
#include "display.h"
#include "data.h"

int bus_count = sizeof(buses) / sizeof(buses[0]);

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);
  numeric.begin(0x74);
  numeric.clear();
  
  matrix.drawBitmap(0, 0, init_icon, 8, 8, LED_ON);
  matrix.writeDisplay();
  
  Serial.println();
  Serial.println();
  Serial.printf("Connecting to %s", ssid);
  WiFi.config(client_ip, dns_ip, gateway_ip);
  WiFi.begin(ssid, password);

  numeric.blinkRate(1);
  numeric.drawColon(true);
  numeric.writeDisplay();
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    Serial.print(".");
  }
 
  Serial.println("");
  
  Serial.println("WiFi connected");

  WiFiClient client;
  client.setNoDelay(true);
  if (!client.connect(host_ip, host_port)) {
    Serial.println("connection failed");
    return;
  }

  Serial.println("Picking bus");
  randomSeed(analogRead(0));
  int i = random(bus_count);
  Serial.printf("Picked bus %d\n", i);

  Serial.println("Sending bus");
  client.write(buses[i].number);

  int next;
  int current_digit = 0;
  numeric.blinkRate(0);
  numeric.clear();

  Serial.println("Drawing arrivals");
  while(client.connected() && current_digit < 5){    
    next = client.read(); // Time to arrival in deciseconds

    if (next == -1) {
      continue; // No data
    }
    
    Serial.printf("Got arrival in %d deciseconds\n", next);

    if (current_digit == 0) {
      Serial.println("Drawing icon");
      matrix.clear();
      matrix.drawBitmap(0, 0, buses[i].icon, 8, 8, LED_ON);
      matrix.writeDisplay();
    }

    int minutes = next / 6;
    if (minutes < 3) {
      continue; 
    }

    int tens = minutes / 10;
    if (tens > 0) {
      if (current_digit > 3) {
        break;
      }

      numeric.writeDigitNum(current_digit, tens);
      current_digit = increment_digit(current_digit);
    }

    numeric.writeDigitNum(current_digit, minutes % 10, true);
    current_digit = increment_digit(current_digit);
  }
  numeric.writeDisplay();
  
  Serial.println();
  Serial.println("closing connection");
}

void loop() {
}
