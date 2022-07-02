// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "ESP8266-Access-Point";
const char* password = "marco_123456789";


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readSteering() {
  return String("Hola segnorita");
}


void setup() {
  // Serial port for debugging purposes
  Serial.begin(2400);
  Serial.println("Gibberish to start");
  //
    // Setting the ESP as an access point
    Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);
//  
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    Serial.println("Setting up device");
  
    server.on("/steering", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send_P(200, "text/plain", readSteering().c_str());
    });
  
    // Start server
  server.begin();
}

void loop() {
      Serial.println("test");
      delay(2000);
}
