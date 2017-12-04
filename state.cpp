#include <ESP8266WiFi.h>

uint8_t state_get() {
  uint8_t index;
  ESP.rtcUserMemoryRead(0, (uint32_t*) &index, 1);
  Serial.printf("Got index %d from RTC\n", index);
  return index;
}

void state_set(uint8_t index) {
  Serial.printf("Storing index %d to RTC\n", index);
  ESP.rtcUserMemoryWrite(0, (uint32_t*) &index, 1);
}

