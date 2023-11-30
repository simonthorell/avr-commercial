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

  // testing
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
