#include "lcd.h"
#include <avr/io.h>

#define Ö "\xEF"
#define Ä "\xE1"
#define Å "\x08" //YOU NEED TO CREATE THE CHARACTER FIRST!
#define customÅ { 0x4 , 0x0 , 0xe , 0x1 , 0xf , 0x11 , 0xf , 0x0}

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize the LCD
  lcd.Initialize();

  // Clear the LCD screen
  lcd.Clear();

  // testing
  unsigned char customCharTwo[8] = {0b10000, 0b01000, 0b00100, 0b00010,
                                    0b00001, 0b00010, 0b00100, 0b01000};
  unsigned char testArray[] = customÅ;
  lcd.CreateChar(0, testArray);
  lcd.CreateChar(1, customCharTwo);
  lcd.Clear();
  char test[] = "En god bilaff" Ä "r (f" Ö "r Harry!)";
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
