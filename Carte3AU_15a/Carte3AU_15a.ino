/*
  Code 15a: Test NRF24L01+ (Basic RX)
*/

/*

Demonstrates simple RX operation with an ESP32.
Any of the Basic_TX examples can be used as a transmitter.

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

const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 15;
const static uint8_t PIN_RADIO_CSN = 12;
const static uint8_t PIN_RADIO_MOSI = 23;
const static uint8_t PIN_RADIO_MISO = 19;
const static uint8_t PIN_RADIO_SCK = 18;

#define csMAX6675 27

struct __attribute__((packed)) RadioPacket // Note the packed attribute.
{
    uint8_t FromRadioId;
    uint32_t OnTimeMillis;
    uint32_t FailedTxCount;
};

NRFLite _radio;
RadioPacket _radioData;

void setup()
{
  pinMode(csMAX6675,OUTPUT);
  digitalWrite(csMAX6675,HIGH); // Deactivate MAX6675
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
    Serial.println("NRFLite Basic RX ready...");
  }
}

void loop()
{
  while (_radio.hasData())
  {
    _radio.readData(&_radioData);

    String msg = "Radio ";
    msg += _radioData.FromRadioId;
    msg += ", ";
    msg += _radioData.OnTimeMillis;
    msg += " ms, ";
    msg += _radioData.FailedTxCount;
    msg += " Failed TX";

    Serial.println(msg);
  }
}
