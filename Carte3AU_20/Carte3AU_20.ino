/*
  Code 20: Test Serial EEPROM 24LC256 (Carte V2.0)

  Source: https://github.com/argandas/serialEEPROM

  Atmel AT24C256 EEPROM Memory
  Device Address 0x50 (A0 = GND, A1 = GND)
  256K bit memory = 32768 Bytes
  64-Byte Page Write Buffer 
*/

#include <Wire.h>
#include <serialEEPROM.h>

serialEEPROM myEEPROM(0x50, 32768, 64);

void setup()
{
	Serial.begin(115200);
	Serial.println("Microchip 24C256 EEPROM Memory Example");
	Wire.begin();
	/* Write byte (Address 0x10) */
	myEEPROM.write(0x10, 0x87);

	/* Read byte (Address 0x10) */
	uint8_t num = 0x00;
	num = myEEPROM.read(0x10);
	Serial.print("Read byte: ");
	Serial.println(num, HEX);

	/* Write buffer (Address 0x30) */
	const char* name = "Hello World!";
	myEEPROM.write(0x30, (uint8_t*)name, strlen(name)+1);

	/* Read buffer (Address 0x30) */
	char aName[16] = {0};
	myEEPROM.read(0x30, (uint8_t*)aName, sizeof(aName));
	Serial.print("Read buffer: ");
	Serial.println(aName);

  /* Dump of Memory */
  Serial.println("Serial EEPROM dump:");
  myEEPROM.dump(Serial,0,32768);
}

void loop()
{
	delay(1000);
}
