/*
  Code 16: Test Buzzer (Carte V2.0)
*/
/*
	EasyBuzzer - Regular Beep Example
	This example shows the different beeps methods.
	Copyright (c) 2017, Evert Arias
	MIT License
 source: https://github.com/evert-arias/EasyBuzzer
*/

#include "EasyBuzzer.h"

int buzzer = 17;
unsigned int frequency = 1000;
unsigned int beeps = 10;

void done()
{
	Serial.println("Done!");
}

void setup()
{
	Serial.begin(115200);
	Serial.print("Starting Buzzer...");
	/* Set the pin where the buzzer is connected */
	EasyBuzzer.setPin(buzzer);
	/* Beep continuously at a given frequency. */
	// EasyBuzzer.beep(frequency);

	/* Beep at a given frequency an specific number of times. */
	// EasyBuzzer.beep(frequency, beeps);

	/* Beep at a given frequency an specific number of times, with callback functionality. */
	EasyBuzzer.beep(frequency, beeps, done);

	/* Use this function to stop the beeping. You may call this function at all time, everywhere in the code. */
	// EasyBuzzer.stopBeep();
}

void loop()
{
	/* Always call this function in the loop for EasyBuzzer to work. */
	EasyBuzzer.update();
}
