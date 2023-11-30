#ifndef __random_h
#define __random_h

#include <avr/io.h>
#include "lcd.h"
#include <stdint.h> //So I dont get all the uint errors, just for my IDE

// typedef struct = {
//   uint16_t factor;
//   uint8_t occurance;
// }factorization;

uint16_t* factorize(uint16_t value, HD44780 *lcd);
void removeCommonFactors(uint16_t ** ptrToArray, uint8_t arrayLength);
uint16_t deFactorize(uint16_t value);

#endif // !__random_h
