#ifndef __avr_random_noise_h
#define __avr_random_noise_h

#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include "lcd.h" //FIXME: Remove when randomTest is gone

//Only here for debug purposes, lets you print out the binary format
//FIXME: Remove when randomTest is gone
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  ((byte) & 0x80 ? '1' : '0'), ((byte) & 0x40 ? '1' : '0'),                    \
      ((byte) & 0x20 ? '1' : '0'), ((byte) & 0x10 ? '1' : '0'),                \
      ((byte) & 0x08 ? '1' : '0'), ((byte) & 0x04 ? '1' : '0'),                \
      ((byte) & 0x02 ? '1' : '0'), ((byte) & 0x01 ? '1' : '0')

void initializeRandom(void);
uint16_t randomValue();
uint16_t getRandom(uint16_t limit);
uint8_t getNumBytes(uint16_t value);
void randomTest(HD44780 *lcd); //FIXME: Remove before release

#endif // !__avr_random_noise_h
