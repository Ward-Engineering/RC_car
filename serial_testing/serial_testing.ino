void setup() {
  // put your setup code here, to run once:
  Serial.begin(2400);
  Serial.println("Gibberish to start");
  Serial.println("hola");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("mark is that you");
  delay(500);
}
