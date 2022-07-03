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

#define Steering 5
#define Throttle 14
#define Brake 12

// REPLACE WITH THE MAC Address of your receiver (the one you'll be sending the data to)
uint8_t broadcastAddress[] = {0xAC, 0x0B, 0xFB, 0xD7, 0xD1, 0xD8};

// Variable to store if sending data was successful
String success;

//Variable to store incoming driver inputs
int incomingSteering;
bool appliedBrake;
bool appliedThrottle;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    int steeringAngle;
    bool brakeApplied;
    bool throttleApplied;
} struct_message;


// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  incomingSteering = incomingReadings.steeringAngle;
  appliedBrake = incomingReadings.brakeApplied;
  appliedThrottle = incomingReadings.throttleApplied;
  analogWrite(Steering,incomingSteering);
  if(appliedBrake){
    digitalWrite(Throttle,LOW);
    digitalWrite(Brake,HIGH);
  }
  else if(appliedThrottle){
    digitalWrite(Throttle,HIGH);
    digitalWrite(Brake,LOW);
  }
  
  else{
    digitalWrite(Throttle,LOW);
    digitalWrite(Brake,LOW);
  }
}


void printIncomingReadings(){
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS in the car");
  Serial.print("Accelerator: ");
  Serial.println(incomingSteering);
}
 
void setup() {
  //assign pins
  pinMode(Steering, INPUT);
  pinMode(Brake,OUTPUT);
  pinMode(Throttle,OUTPUT);

  // Init Serial Monitor
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

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
}
