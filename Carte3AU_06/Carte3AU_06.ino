/*
  Code 06: Test Potentiometer (GPIO33 = ADC1 Channel 5) and Relay (GPIO25)
*/


// Potentiometer is connected to GPIO 33 (Analog ADC1_CH5) 
const int potPin = 33;

// Relay is connected to GPIO 25
const int relayPin = 25;
const int TempThreshold = 2100;

// variable for storing the potentiometer value
int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Relay is OFF
}

void loop() {
  // Reading potentiometer value
  potValue = analogRead(potPin);
  Serial.println(potValue);
  if (potValue < TempThreshold)
    digitalWrite(relayPin, HIGH); // Relay is ON
  else
    digitalWrite(relayPin, LOW); // Relay is OFF
  delay(500);
}
