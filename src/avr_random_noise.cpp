#include "avr_random_noise.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

void initializeRandom(void) {
  PRR &= ~(1 << PRADC);                    // Turn on power to the ADC
  ADMUX &= ~((1 << REFS0) | (1 << REFS1)); // set VCC as voltage reference
  ADMUX |= PD3;                            // Start pin 3
  ADCSRA |=
      ((1 << ADPS0) |
       (1 << ADPS1));    // set the speed, lower speed needed for10bit accuracy
  ADCSRA |= (1 << ADEN); // Start the ADC
  return;
}

uint16_t randomValue(uint16_t maxInclusive) {
  uint16_t rnd = 0;
  ADCSRA |= (1 << ADSC);         // set the ADSC bit
  while (ADCSRA & (1 << ADSC)) { // wait until its cleared, we have data then
    asm(""); // dirty hack to make sure the loop doesnt get optimized out
  }
  rnd = ADCL;         // read lower 8 bits
  rnd += (ADCH << 8); // read the high 2 bits

  return rnd;
}

uint16_t getRandom(uint8_t numBytes) {
  uint16_t value = 0;
  uint16_t rnd;
  for (uint8_t i = 0; i < numBytes * 4; i++) {
    rnd = randomValue(0);
    rnd = rnd & 0x3;
    value += rnd << i * 2;
  }
  return value;
}
