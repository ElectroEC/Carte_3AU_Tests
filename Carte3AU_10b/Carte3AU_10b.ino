/*
  Code 10b: Test Keyboard on MCP23017 + OLED Display
*/

/**
 * This example shows how to use the matrix keyboard support that's built into IoAbstraction,
 * it can be used out the box with either a 3x4 or 4x4 keypad, but you can modify it to use
 * any matrix keyboard quite easily.
 * It just sends the characters that are typed on the keyboard to Serial. The keyboard in This
 * example is connected directly to Arduino pins, but could just as easily be connected over
 * a PCF8574, MCP23017 or other IoAbstraction.
 */

#include <Wire.h>
#include <IoAbstraction.h>
#include <IoAbstractionWire.h>
#include<TaskManagerIO.h>
#include <KeyboardManager.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display
#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT   64 // OLED display height, in pixels
#define OLED_RESET      -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Keypad I/O with MCP23017
#define ROW1 8  // GPB0
#define ROW2 9  // GPB1
#define ROW3 10 // GPB2
#define ROW4 11 // GPB3
#define COL1 12 // GPB4
#define COL2 13 // GPB5
#define COL3 14 // GPB6
#define COL4 15 // GPB7

//
// We need to make a keyboard layout that the manager can use. choose one of the below.
// The parameter in brackets is the variable name.
//
//MAKE_KEYBOARD_LAYOUT_3X4(keyLayout)
MAKE_KEYBOARD_LAYOUT_4X4(keyLayout)

//
// We need a keyboard manager class too
//
MatrixKeyboardManager keyboard;

// this examples connects the pins directly to an arduino but you could use
// IoExpanders or shift registers instead.
IoAbstractionRef ioExpander = ioFrom23017(0x20);

//
// We need a class that extends from KeyboardListener. this gets notified when
// there are changes in the keyboard state.
//
class MyKeyboardListener : public KeyboardListener {
public:
    void keyPressed(char key, bool held) override {
        Serial.print("Key ");
        Serial.print(key);
        Serial.print(" is pressed, held = ");
        Serial.println(held);
        display.clearDisplay();   
        display.setCursor(0, 0);
        display.print(F("Key: "));  
        display.print(key);  
        display.display();      // Show initial text
    }

    void keyReleased(char key) override {
        Serial.print("Released ");
        Serial.println(key);
    }
} myListener;

void setup() {
  Wire.begin(); // Don't forget to call this function for initialise Wire (I2C)
  Serial.begin(115200);
  delay(1000);

  // OLED Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
    
  // Keyboard
  keyLayout.setRowPin(0, ROW1);
  keyLayout.setRowPin(1, ROW2);
  keyLayout.setRowPin(2, ROW3);
  keyLayout.setRowPin(3, ROW4);
  keyLayout.setColPin(0, COL1);
  keyLayout.setColPin(1, COL2);
  keyLayout.setColPin(2, COL3);
  keyLayout.setColPin(3, COL4);

  // create the keyboard mapped to arduino pins and with the layout chosen above.
  // it will callback our listener
  keyboard.initialise(ioExpander, &keyLayout, &myListener);

  // start repeating at 850 millis then repeat every 350ms
  keyboard.setRepeatKeyMillis(850, 350);

  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Key: "));  
  display.display();      // Show initial text

  Serial.println("Keyboard is initialised!");
}

void loop() {
  // as this indirectly uses taskmanager, we must include this in loop.
  taskManager.runLoop();
}
