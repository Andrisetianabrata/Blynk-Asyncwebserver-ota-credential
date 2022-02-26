#define BLYNK_PRINT Serial
#include "FS.h"
#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LITTLEFS.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <LittleFS.h>
#define LITTLEFS LittleFS
#endif


#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#include "index.h"

char auth[50];
char ssid[50];
char pass[50];


char H_ssid[] = "HOME SWITCH";
char H_pass[] = "123456789";


AsyncWebServer server(80);
IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

const byte tombol = 13;
String input;
bool event_connection = !true;

void writeFile(const char * path, const char * message);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

void setup()
{
  pinMode(tombol, INPUT_PULLUP);
  if(digitalRead(tombol) == LOW) event_connection = true; 
  Serial.begin(115200);
  if(!LITTLEFS.begin()){
      Serial.println("LITTLEFS Mount Failed");
      return;
  }
  File file = LITTLEFS.open("/config.json", "r");

  if(!file || file.isDirectory())
  {
    String output;
    StaticJsonDocument<512> doc;

    doc["ssid"] = "admin";
    doc["pass"] = "";
    doc["auth"] = "";

    serializeJson(doc, output);
    writeFile("/config.json",output.c_str());
    ESP.restart();
  }else{
    input = file.readStringUntil('\n');
    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, input);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

     strlcpy(ssid, doc["ssid"] | "", sizeof(ssid));
     strlcpy(pass, doc["pass"] | "", sizeof(pass));
     strlcpy(auth, doc["auth"] | "", sizeof(auth));
     Serial.println(ssid);
     Serial.println(pass);
     Serial.println(auth);
  }


  if(event_connection == true)
  {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(H_ssid,H_pass);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    Serial.println(local_ip);
  }else{
    Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);
  }
  server.on("/", [](AsyncWebServerRequest * request) {
  request->send_P(200, "text/html", _webpage);
});

// Send a GET request to <IP>/get?message=<message>
server.on("/data", HTTP_GET, [] (AsyncWebServerRequest * request) {
  if (request->hasParam("auth") && request->hasParam("pass") && request->hasParam("ssid")) {
      String C_auth, C_pass, C_ssid;
      C_auth = request->getParam("auth")->value();
      C_ssid = request->getParam("ssid")->value();
      C_pass = request->getParam("pass")->value();
      String output;
      Serial.println(C_ssid);
      Serial.println(C_pass);
      Serial.println(C_auth);
      StaticJsonDocument<512> doc;

      doc["ssid"] = C_ssid;
      doc["pass"] = C_pass;
      doc["auth"] = C_auth;

      serializeJson(doc, output);
      writeFile("/config.json",output.c_str());
  } else {
    request->send_P(200, "text/html", "NO DATA SENT");
  }
  request->send_P(200, "text/html", success);
  ESP.restart();
});

server.onNotFound(notFound);
server.begin();
}

void loop()
{
  Blynk.run();
}


void writeFile(const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = LittleFS.open(path, "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  delay(2000); // Make sure the CREATE and LASTWRITE times are different
  file.close();
}