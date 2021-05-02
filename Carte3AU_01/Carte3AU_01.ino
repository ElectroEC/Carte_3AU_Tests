/*
  Code 01: Test LED RGB
*/

#define LED_R 16
#define LED_G 13
#define LED_B 17

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_R, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // wait for a second
  digitalWrite(LED_R, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_G, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
  digitalWrite(LED_G, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED_B, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                 // wait for a second
  digitalWrite(LED_B, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_R, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_G, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
  digitalWrite(LED_R, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_B, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // wait for a second
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_R, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
  digitalWrite(LED_G, HIGH);
  delay(2000);
  digitalWrite(LED_R, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_G, LOW);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_B, LOW);    // turn the LED off by making the voltage LOW
}
