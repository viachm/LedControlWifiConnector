#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index.h"

const char* ssid = "SSID";
const char* password = "PASSWORD";
const int LED_PIN = 16;
int currentOutput = 1;
int currentProgramType = 1;
MDNSResponder mdns;
ESP8266WebServer server(80);

void runBlinkProgram() {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
}

void runSmoothProgram() {
    analogWrite(LED_PIN, currentOutput);
    delay(10);

    if (++currentOutput >= 255) {
      currentOutput = 0;
    }
}

void handleRoot() {
  if (!server.hasArg("LED")) return server.send(200, "text/html", INDEX_HTML);
  String LEDvalue = server.arg("LED");

  if (LEDvalue == "1") {
    currentProgramType = 1;
    server.send(200, "text/html", INDEX_HTML);
  } else if (LEDvalue == "2") {
    currentProgramType = 2;
    server.send(200, "text/html", INDEX_HTML);
  } else if (LEDvalue == "3") {
    currentProgramType = 3;
    server.send(200, "text/html", INDEX_HTML);
  } else if (LEDvalue == "4") {
    currentProgramType = 4;
    server.send(200, "text/html", INDEX_HTML);
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("espControl", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.print("Connect to http://espControl.local or http://");
  Serial.println(WiFi.localIP());
}

void handleProgram() {
  if (currentProgramType == 1) {
    runBlinkProgram();
  } else if (currentProgramType == 2) {
    runSmoothProgram();
  } else if (currentProgramType == 3) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
}

void loop(void) {
  server.handleClient();
  handleProgram();
}
