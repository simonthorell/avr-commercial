#ifndef __avr_random_noise_h
#define __avr_random_noise_h

#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE

void initializeRandom(void);
uint16_t randomValue(uint16_t maxInclusive);
uint16_t getRandom(uint8_t numBytes);

#endif // !__avr_random_noise_h
