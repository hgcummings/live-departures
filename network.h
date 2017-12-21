#include <ESP8266WiFi.h>

extern char* ssid;
extern char* password;

extern IPAddress local_ip;
extern IPAddress gateway_ip;
extern IPAddress subnet_mask;

extern IPAddress host_ip;
extern uint16_t host_port;

WiFiClient network_client(void (*spinner)());
