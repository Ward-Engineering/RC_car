#include <ESP8266Wifi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "RC_car_dangerous"; // Enter your WiFi name
const char *password = "marco_borsato";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp8266/test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;


void setup() {
  // Set software serial baud to 115200;
  Serial.begin(2400);
  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
}
    

}

void loop() {
  // put your main code here, to run repeatedly:

}
