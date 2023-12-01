#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

//Only here for debug purposes, lets you print out the binary format
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  ((byte) & 0x80 ? '1' : '0'), ((byte) & 0x40 ? '1' : '0'),                    \
      ((byte) & 0x20 ? '1' : '0'), ((byte) & 0x10 ? '1' : '0'),                \
      ((byte) & 0x08 ? '1' : '0'), ((byte) & 0x04 ? '1' : '0'),                \
      ((byte) & 0x02 ? '1' : '0'), ((byte) & 0x01 ? '1' : '0')

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize & clear the LCD
  lcd.Initialize();
  lcd.Clear();
  initializeRandom();

  uint16_t rnd = 0;
  uint8_t rndLow = 0;
  uint8_t rndHigh = 0;
  char rndBuff[30];
  while (1) {
    lcd.Clear();
    lcd.GoTo(0, 0);
    rnd = getRandom(2);
    rndLow = rnd & 0xff;
    rndHigh = rnd >> 8;
    sprintf(rndBuff, "%u", rnd);
    lcd.WriteText(rndBuff);
    sprintf(rndBuff, BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN,
            BYTE_TO_BINARY(rndHigh), BYTE_TO_BINARY(rndLow));
    lcd.GoTo(0, 1);
    lcd.WriteText(rndBuff);
    _delay_ms(500);
  }
  return 0;
}
