/*
  Code 02: Test Buttons (BP401, BP402 & BT401)
*/

// set pin numbers
const int touchPin = 14;
const int button1Pin = 0;
const int button2Pin = 36;
const int ledPin = 16;

// structure for buttons
struct Button
{
  const uint8_t PIN;
  volatile uint32_t numberKeyPresses;
  volatile bool pressed;
};

Button button1 = {button1Pin, 0, false};
Button button2 = {button2Pin, 0, false};

void IRAM_ATTR button1_isr()
{
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}

void IRAM_ATTR button2_isr()
{
  button2.numberKeyPresses += 1;
  button2.pressed = true;
}

// change with your threshold value
const int threshold = 35;
// variable for storing the touch pin value
int touchValue;
int dummyTouchValue;

void setup()
{
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(button1.PIN, INPUT);
  attachInterrupt(button1.PIN, button1_isr, FALLING);
  pinMode(button2.PIN, INPUT);
  attachInterrupt(button2.PIN, button2_isr, RISING);
}

void loop()
{
  // read the state of the pushbutton value:
  delay(50);
  dummyTouchValue = touchRead(touchPin);
  delay(50);
  touchValue = touchRead(touchPin);
  touchValue = touchValue > dummyTouchValue ? touchValue : dummyTouchValue;
  //Serial.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if (touchValue < threshold)
  {
    // turn LED on
    digitalWrite(ledPin, HIGH);
    //Serial.println(" - LED on");
  }
  else
  {
    // turn LED off
    digitalWrite(ledPin, LOW);
    //Serial.println(" - LED off");
  }
  if (button1.pressed)
  {
    Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
    button1.pressed = false;
  }
  if (button2.pressed)
  {
    Serial.printf("Button 2 has been pressed %u times\n", button2.numberKeyPresses);
    button2.pressed = false;
  }
  //delay(50);
}
