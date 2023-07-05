/*
  Code 03: MCP23017 & 7 Segments Display
*/

#include <Wire.h>
#include <Adafruit_MCP23X17.h>
// #include "Adafruit_MCP23017.h"

Adafruit_MCP23X17 mcp;
#define BCD_A 0
#define BCD_B 1
#define BCD_C 2
#define BCD_D 3
#define DIGIT_1 4
#define DIGIT_2 5
#define DIGIT_3 6
#define DIGIT_4 7

void setup()
{
  mcp.begin_I2C(); // use default address 0
  mcp.pinMode(BCD_A, OUTPUT);
  mcp.pinMode(BCD_B, OUTPUT);
  mcp.pinMode(BCD_C, OUTPUT);
  mcp.pinMode(BCD_D, OUTPUT);
  mcp.pinMode(DIGIT_1, OUTPUT);
  mcp.pinMode(DIGIT_2, OUTPUT);
  mcp.pinMode(DIGIT_3, OUTPUT);
  mcp.pinMode(DIGIT_4, OUTPUT);
  mcp.digitalWrite(DIGIT_1, HIGH);
  mcp.digitalWrite(DIGIT_2, HIGH);
  mcp.digitalWrite(DIGIT_3, HIGH);
  mcp.digitalWrite(DIGIT_4, HIGH);
}

void loop()
{
  for (byte i = 0; i < 10; i++)
  {
    displayDecimal(i);
    delay(200);
  }
}

void displayDecimal(byte number)
{
  bool val_BCD_A, val_BCD_B, val_BCD_C, val_BCD_D;

  switch (number)
  {
  case 0:
    val_BCD_A = LOW, val_BCD_B = LOW, val_BCD_C = LOW, val_BCD_D = LOW;
    break;
  case 1:
    val_BCD_A = HIGH, val_BCD_B = LOW, val_BCD_C = LOW, val_BCD_D = LOW;
    break;
  case 2:
    val_BCD_A = LOW, val_BCD_B = HIGH, val_BCD_C = LOW, val_BCD_D = LOW;
    break;
  case 3:
    val_BCD_A = HIGH, val_BCD_B = HIGH, val_BCD_C = LOW, val_BCD_D = LOW;
    break;
  case 4:
    val_BCD_A = LOW, val_BCD_B = LOW, val_BCD_C = HIGH, val_BCD_D = LOW;
    break;
  case 5:
    val_BCD_A = HIGH, val_BCD_B = LOW, val_BCD_C = HIGH, val_BCD_D = LOW;
    break;
  case 6:
    val_BCD_A = LOW, val_BCD_B = HIGH, val_BCD_C = HIGH, val_BCD_D = LOW;
    break;
  case 7:
    val_BCD_A = HIGH, val_BCD_B = HIGH, val_BCD_C = HIGH, val_BCD_D = LOW;
    break;
  case 8:
    val_BCD_A = LOW, val_BCD_B = LOW, val_BCD_C = LOW, val_BCD_D = HIGH;
    break;
  case 9:
    val_BCD_A = HIGH, val_BCD_B = LOW, val_BCD_C = LOW, val_BCD_D = HIGH;
    break;
  }
  mcp.digitalWrite(BCD_A, val_BCD_A);
  mcp.digitalWrite(BCD_B, val_BCD_B);
  mcp.digitalWrite(BCD_C, val_BCD_C);
  mcp.digitalWrite(BCD_D, val_BCD_D);
}
