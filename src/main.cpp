#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize & clear the LCD
  lcd.Initialize();
  lcd.Clear();
  initializeRandom();
  randomTest(&lcd);

  while (1) {
  }
  return 0;
}
