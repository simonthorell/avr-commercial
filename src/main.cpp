#include "lcd.h"
#include <avr/io.h>

#define replaceÖ (char)0xEF
#define replaceÄ (char)0xE1

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize the LCD
  lcd.Initialize();

  // Clear the LCD screen
  lcd.Clear();

  // Define the text to be displayed
  char text[] = "abc";

  // very good looking å
  unsigned char customChar[8] = {0b00100, 0b00000, 0b01110, 0b00001,
                                 0b01111, 0b10001, 0b01111, 0b00000};
  // testing
  unsigned char customCharTwo[8] = {0b10000, 0b01000, 0b00100, 0b00010,
                                    0b00001, 0b00010, 0b00100, 0b01000};
  lcd.CreateChar(0, customChar);
  lcd.CreateChar(1, customCharTwo);
  lcd.Clear();
  char test[5];
  // Address for first custom character is 8 for some reason?
  test[0] = 0x8;
  test[1] = replaceÄ;
  test[2] = replaceÖ;
  // second address is 9? Idk it should be 0 and 1
  test[3] = 0x9;
  test[4] = 0x0;
  lcd.WriteText(test);
  lcd.GoTo(0, 1);
  lcd.WriteText(text);
  // The microcontroller typically runs in an infinite loop
  while (1) {
    // Your main program logic here
    // If you want to update the display, you can call lcd.WriteText with new
    // text
  }

  return 0;
}
