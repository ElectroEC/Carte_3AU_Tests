/*
  Code 15b: Test NRF24L01+ (Basic TX)
*/

/*

Demonstrates simple TX operation with an ESP32.
Any of the Basic_RX examples can be used as a receiver.

Complication with ESP's requires the use of '__attribute__((packed))' on the RadioPacket data structure
to ensure the bytes within the structure are aligned properly in memory.

The ESP32 SPI library supports configurable SPI pins and NRFLite's mechanism to support this is shown.

Radio    ESP32 module
CE    -> 4
CSN   -> 5
MOSI  -> 23
MISO  -> 19
SCK   -> 18
IRQ   -> No connection
VCC   -> No more than 3.6 volts
GND   -> GND

*/

#include <SPI.h>
#include <NRFLite.h>

const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 15;
const static uint8_t PIN_RADIO_CSN = 12;
const static uint8_t PIN_RADIO_MOSI = 23;
const static uint8_t PIN_RADIO_MISO = 19;
const static uint8_t PIN_RADIO_SCK = 18;

#define csMAX6675 27
#define LED_STATUS 16
#define BP 36

struct __attribute__((packed)) RadioPacket // Note the packed attribute.
{
    uint8_t FromRadioId;
    uint32_t OnTimeMillis;
    uint32_t FailedTxCount;
};

NRFLite _radio;
RadioPacket _radioData;

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup()
{
  pinMode(csMAX6675,OUTPUT);
  digitalWrite(csMAX6675,HIGH); // Deactivate MAX6675
  pinMode(LED_STATUS, OUTPUT);
  pinMode(BP,INPUT);  
  Serial.begin(115200);
  
  // Configure SPI pins.
  SPI.begin(PIN_RADIO_SCK, PIN_RADIO_MISO, PIN_RADIO_MOSI, PIN_RADIO_CSN);
  
  // Indicate to NRFLite that it should not call SPI.begin() during initialization since it has already been done.
  uint8_t callSpiBegin = 0;
  
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, 100, callSpiBegin))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
  else
  {
    Serial.println("NRFLite Basic TX ready...");
  }
  
  _radioData.FromRadioId = RADIO_ID;  
}

void loop()
{
  // read the pushbutton input pin:
  buttonState = digitalRead(BP);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      digitalWrite(LED_STATUS,HIGH); // LED On
      
      _radioData.OnTimeMillis = millis();
      
      Serial.print("Sending ");
      Serial.print(_radioData.OnTimeMillis);
      Serial.print(" ms");
  
      // By default, 'send' transmits data and waits for an acknowledgement.  If no acknowledgement is received,
      // it will try again up to 16 times.  This retry logic is built into the radio hardware itself, so it is very fast.
      // You can also perform a NO_ACK send that does not request an acknowledgement.  In this situation, the data packet
      // will only be transmitted a single time and there is no verification of delivery.  So NO_ACK sends are suited for
      // situations where performance is more important than reliability.
      //   _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::REQUIRE_ACK) // THE DEFAULT
      //   _radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData), NRFLite::NO_ACK)
      
      if (_radio.send(DESTINATION_RADIO_ID, &_radioData, sizeof(_radioData))) // Note how '&' must be placed in front of the variable name.
      {
          Serial.println("...Success");
      }
      else
      {
          Serial.println("...Failed");
          _radioData.FailedTxCount++;
      }
      digitalWrite(LED_STATUS,LOW); // LED Off    
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;
}
