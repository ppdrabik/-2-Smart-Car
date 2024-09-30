#include "LoRa.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>


ESP8266WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
StaticJsonDocument <200> doc;


const char *ssid = "POCO F2 Pro";
const char *password = "haslo123";


void WIFI_Init();
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void LOAD_Html();
void LOAD_CSS();
void LOAD_JS();


typedef struct
{
	int8_t x;
	int8_t y;
  int8_t data[2];
}axis_s;

static axis_s axis;

void setup() 
{
  Serial.begin(115200);
  lora_s lora =
  {
	.bandwidth = khz_125,
	.sf = SF_10,
	.pa_boost = true,
	.max_power = 3,
	.output_power = 14,
	.lna_gain = 6
  };

  LoRa_Init(&lora);
  LoRa_Init_Transmit();

  delay(50);
  LittleFS.begin();
  delay(50);
  WIFI_Init();
  delay(50);
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  server.on( "/" , LOAD_Html);
  server.on( "/style.css", LOAD_CSS);
  server.on( "/script.js", LOAD_JS);
  server.begin();
  delay(5);
}


void loop() 
{   
    server.handleClient();
    webSocket.loop();
}


void WIFI_Init()
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.print("IP addresss:\t");
  Serial.println(WiFi.localIP());
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  switch (type)
  {
    case WStype_DISCONNECTED:
      {
        Serial.printf("[%u] Disconnected!\n", num);
      }
      break;

    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        
      }
      break;

    case WStype_TEXT:
      {
        Serial.printf("[%u] get Text: %s\n", num, payload);
        DeserializationError error = deserializeJson(doc, (char*)payload);
        axis.x = doc["x"];
        axis.y = doc["y"];
        axis.data[0] = axis.x;
        axis.data[1] = axis.y;
        LoRa_Transmit_8(axis.data, 2);
        Serial.println("Transmit..");
      }
      break;
  }
}

void LOAD_Html()
{
  File f = LittleFS.open("/index.html", "r");
  server.streamFile(f, "text/html");
  f.close();
}

void LOAD_CSS()
{
  File f = LittleFS.open("/style.css", "r");
  server.streamFile(f, "text/css");
  f.close();
}

void LOAD_JS()
{
  File f = LittleFS.open("/script.js", "r");
  server.streamFile(f, "application/javascript");
  f.close();
}

