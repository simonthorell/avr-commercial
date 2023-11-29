#include "lcd.h"
#include <avr/io.h>

#define Ö "\xEF"
#define Ä "\xE1"
#define Å "\x08" //YOU NEED TO CREATE THE CHARACTER FIRST!

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize the LCD
  lcd.Initialize();

  // Clear the LCD screen
  lcd.Clear();

  // very good looking å
  unsigned char customChar[8] = {0b00100, 0b00000, 0b01110, 0b00001,
                                 0b01111, 0b10001, 0b01111, 0b00000};
  // testing
  unsigned char customCharTwo[8] = {0b10000, 0b01000, 0b00100, 0b00010,
                                    0b00001, 0b00010, 0b00100, 0b01000};
  lcd.CreateChar(0, customChar);
  lcd.CreateChar(1, customCharTwo);
  lcd.Clear();
  char test[] = Å Ä Ö " WOW!";
  // Address for first custom character is 8 for some reason?
  lcd.WriteText(test);
  // The microcontroller typically runs in an infinite loop
  while (1) {
    // Your main program logic here
    // If you want to update the display, you can call lcd.WriteText with new
    // text
  }

  return 0;
}
