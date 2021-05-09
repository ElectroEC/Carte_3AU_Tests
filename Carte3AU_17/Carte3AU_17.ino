/*
  Code 17: Test Led WS2812B (Carte V2.0)
  
  Source: https://github.com/Freenove/Freenove_WS2812_Lib_for_ESP32
*/

#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  1
#define LEDS_PIN	  0
#define CHANNEL		  0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

u8 m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
int delayval = 100;

void setup() {
	strip.begin();
	strip.setBrightness(10);	
}
void loop() {
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < LEDS_COUNT; i++) {
			strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);
			strip.show();
			delay(delayval);
		}
		delay(500);
	}
}
