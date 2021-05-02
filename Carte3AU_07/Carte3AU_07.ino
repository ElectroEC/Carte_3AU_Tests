/*
  Code 07: Test LDR (GPIO39 = ADC1 Channel 3)
*/

#include <CAN.h>

// LDR is connected to GPIO 39 (Analog ADC1_CH3) 
const int ldrPin = 39;

// variable for storing the LDR value
int ldrValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // Reading LDR value
  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);
  delay(500);
}
