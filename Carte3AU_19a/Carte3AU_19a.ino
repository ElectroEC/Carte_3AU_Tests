/*
  Code 19a: Test MCP4725A1T-E (Carte V2.0)
*/

#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

void setup(void) {
  Serial.begin(115200);
  dac.begin(0x62); // MCP4725A1 the address is 0x62 (default)
  Serial.println("DAC Output testing");
}

void loop(void) {
  Serial.println("Vout = 0V");  
  dac.setVoltage(0, false); // Vout = 0V
  delay(5000);
  Serial.println("Vout = 1.66V");   
  dac.setVoltage(2048, false); // Vout = 1.65V
  delay(5000);
  Serial.println("Vout = 3.3V"); 
  dac.setVoltage(4095, false); // Vout = 3.3V
  delay(5000);  
}
