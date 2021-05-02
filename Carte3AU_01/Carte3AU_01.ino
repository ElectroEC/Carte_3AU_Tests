/*
  Code 01: Test LED RGB
*/

#define LED_R 16
#define LED_G 13
#define LED_B 17

// the setup function runs once when you press reset or power the board
void setup()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW); // turn the LED Red Off
  digitalWrite(LED_G, LOW); // turn the LED Green Off
  digitalWrite(LED_B, LOW); // turn the LED Blue Off
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(LED_R, HIGH); // turn the LED Red On
  delay(1000);               // wait for a second
  digitalWrite(LED_R, LOW);  // turn the LED Red Off
  digitalWrite(LED_G, HIGH); // turn the LED Green On
  delay(1000);               // wait for a second
  digitalWrite(LED_G, LOW);  // turn the LED Green Off
  digitalWrite(LED_B, HIGH); // turn the LED Blue On
  delay(1000);               // wait for a second
  digitalWrite(LED_B, LOW);  // turn the LED Blue Off
  digitalWrite(LED_R, HIGH); // turn the LED Red On
  digitalWrite(LED_G, HIGH); // turn the LED Green On
  delay(1000);               // wait for a second
  digitalWrite(LED_R, LOW);  // turn the LED Red Off
  digitalWrite(LED_B, HIGH); // turn the LED Blue On
  delay(1000);               // wait for a second
  digitalWrite(LED_G, LOW);  // turn the LED Green Off
  digitalWrite(LED_R, HIGH); // turn the LED Red On
  delay(1000);               // wait for a second
  digitalWrite(LED_G, HIGH); // turn the LED Green On
  delay(2000);               // wait for two seconds
  digitalWrite(LED_R, LOW);  // turn the LED Red Off
  digitalWrite(LED_G, LOW);  // turn the LED Green Off
  digitalWrite(LED_B, LOW);  // turn the LED Blue Off
}
