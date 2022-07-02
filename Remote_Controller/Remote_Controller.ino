#define LED1 5
#define Gas A0

int sensorValue = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(Gas,INPUT);
  Serial.begin(2400);
  Serial.println("Commencing operation 66");

}

void loop() {
  sensorValue = analogRead(Gas);
  Serial.println(sensorValue);
  
  digitalWrite(LED1,HIGH);
  delay(500);
  digitalWrite(LED1,LOW);
  delay(500);

}
