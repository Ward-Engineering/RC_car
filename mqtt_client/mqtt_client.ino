#include "EspMQTTClient.h"

EspMQTTClient client(
  "RC_car_wifi_danger",
  "marco_borsato",
  "192.168.1.100",  // MQTT Broker server ip
  "MQTTUsername",   // Can be omitted if not needed
  "MQTTPassword",   // Can be omitted if not needed
  "TestClient"      // Client name that uniquely identify your device
);

void setup() {}

void onConnectionEstablished() {

  client.subscribe("mytopic/test", [] (const String &payload)  {
    Serial.println(payload);
  });

  client.publish("mytopic/test", "This is a message");
}

void loop() {
  client.loop();
}
