#include "lcd.h"
#include <avr/io.h>
#include "lcd_display_options.h"


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
  char test[] = "En god bil" AA "ff" AE "r (f" OE "r Harry!)";
  lcd.WriteText(test);
  _delay_ms(2500);
  char text1[] = "Welcome to      awesome company!";
  char text2[] = "This is a rolling commercial!";
  // The microcontroller typically runs in an infinite loop
  while (1) {
    displayText(lcd, text1);
    _delay_ms(2000);
    displayScrollingText(lcd, text2, sizeof(text2) / sizeof(char));
  }

  return 0;
}
