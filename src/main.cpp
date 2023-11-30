#include "lcd.h"
#include <avr/io.h>

#define OE "\xEF"
#define AE "\xE1"
#define AA "\x08"

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize the LCD
  lcd.Initialize();

  // Clear the LCD screen
  lcd.Clear();

  // testing
  lcd.Clear();
  char test[] = "En god bil" AA "ff" AE "r (f" OE "r Harry!)";
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
