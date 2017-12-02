#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <ESP8266WiFi.h>

#include "network.h"
#include "display.h"

typedef struct {
  unsigned char number;
  uint8_t icon[8];
} service;

static const uint8_t init_icon[8] PROGMEM = {
  B00111100,
  B01111110,
  B01100110,
  B11111111,
  B11111111,
  B01100110,
  B01111110,
  B00111100
};

static const service buses[] PROGMEM = {
  { 43,
    { B10110101,
      B10010101,
      B10010101,
      B10110111,
      B10010001,
      B10010001,
      B10110001,
      B00000000
    }
  },
  { 134,
    { B10110101,
      B10010101,
      B10010101,
      B10110111,
      B10010001,
      B10010001,
      B10110001,
      B00000000
    }
  }
};

int bus_count = sizeof(buses) / sizeof(buses[0]);

int increment_digit(int digit) {
  if (digit == 1) {
    return 3;
  } else {
    return digit + 1;
  }
}

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);
  numeric.begin(0x74);
  
  matrix.clear();
  numeric.clear();
  
  matrix.drawBitmap(0, 0, init_icon, 8, 8, LED_ON);
  matrix.writeDisplay();
  
  Serial.println();
  Serial.println();
  WiFi.config(client_ip, dns_ip, gateway_ip);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
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

  int next;
  int current_digit = 0;
  numeric.blinkRate(0);
  numeric.clear();
  while(client.connected() && current_digit < 5){    
    next = client.read(); // Time to arrival in deciseconds

    if (next == -1) {
      continue; // No data
    }
    
    Serial.printf("Got arrival in %d deciseconds\n", next);

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
