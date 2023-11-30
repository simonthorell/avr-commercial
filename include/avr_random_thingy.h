#ifndef __random_h
#define __random_h

#include <avr/io.h>
#include "lcd.h"

// typedef struct = {
//   uint16_t factor;
//   uint8_t occurance;
// }factorization;

void factorize(uint16_t value, HD44780 *lcd);

#endif // !__random_h
