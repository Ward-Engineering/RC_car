/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-two-way-communication-esp8266-nodemcu/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

#define Steering A0
#define Throttle 5
#define Brake 4


// REPLACE WITH THE MAC Address of your receiver 
uint8_t broadcastAddress[] = {0xAC, 0x0B, 0xFB, 0xD7, 0x7D, 0x92};

//variable to store analog input reading
int steeringAngle;
int prevSteeringAngle;
bool throttleApplied;
bool prevThrottleApplied;
bool brakeApplied;
bool prevBrakesApplied;

// Updates communication every 100 milliseconds
const long interval = 10; 
unsigned long previousMillis = 0;    // will store last time DHT was updated 

// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int steeringAngle;
    bool brakeApplied;
    bool throttleApplied;
} struct_message;

// Create a struct_message called DHTReadings to hold sensor readings
struct_message inputReadings;


// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  if (sendStatus != 0){
    Serial.println("Delivery fail");
  }
}
void pollInputs(){
  // Read accelerator position
  steeringAngle = analogRead(Steering);
  steeringAngle = steeringAngle>>2;
  brakeApplied = digitalRead(Brake);
  throttleApplied = digitalRead(Throttle);
  if((prevSteeringAngle != steeringAngle) || (prevBrakesApplied != brakeApplied) || (prevThrottleApplied != throttleApplied)){
    //Set values to send
    inputReadings.steeringAngle = steeringAngle;
    inputReadings.brakeApplied = brakeApplied;
    inputReadings.throttleApplied = throttleApplied;
    esp_now_send(broadcastAddress, (uint8_t *) &inputReadings, sizeof(inputReadings));
    Serial.println("Send a new value");
    Serial.println(steeringAngle);
    prevSteeringAngle = steeringAngle;
    prevBrakesApplied = brakeApplied;
    prevThrottleApplied = throttleApplied;
  }
}
 
void setup() {
  //assign pins 
  pinMode(Steering,INPUT);

  //setup serial monitor
  Serial.begin(4800);
  Serial.println("Commencing operation 66");

 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else
    Serial.println("Succesfull initialized esp-now");

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
}
 
void loop() {
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {

    // save the last time you updated the DHT values
    previousMillis = currentMillis;

    //Get DHT readings
    pollInputs();
  }
}
