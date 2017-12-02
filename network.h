#include <ESP8266WiFi.h>

extern char* ssid;
extern char* password;

extern IPAddress client_ip;
extern IPAddress dns_ip;
extern IPAddress gateway_ip;

extern IPAddress host_ip;
extern uint16_t host_port;

WiFiClient network_client();
