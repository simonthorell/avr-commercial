#include "avr_random_thingy.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

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

// Probably put a table into progmem?
// I hate this so much but it works
// TODO: Replace with a map if possible, maybe in progmem?
uint16_t indexSwitch(uint16_t value) {
  switch (value) {
  case 2:
    return 0;
  case 3:
    return 1;
  case 5:
    return 2;
  case 7:
    return 3;
  case 11:
    return 4;
  case 13:
    return 5;
  case 17:
    return 6;
  case 19:
    return 7;
  case 23:
    return 8;
  case 29:
    return 9;
  case 31:
    return 10;
  case 37:
    return 11;
  case 41:
    return 12;
  case 43:
    return 13;
  case 47:
    return 14;
  case 53:
    return 15;
  case 59:
    return 16;
  case 61:
    return 17;
  case 67:
    return 18;
  case 71:
    return 19;
  case 73:
    return 20;
  case 79:
    return 21;
  case 83:
    return 22;
  case 89:
    return 23;
  case 97:
    return 24;
  default:
    return 0;
  }
}

uint16_t *factorize(uint16_t value, HD44780 *lcd) {
  uint16_t *factors = (uint16_t *)malloc(sizeof(uint16_t) * 25);
  // Need to clear the memory since we only do a nullcheck later on
  for (uint8_t i = 0; i < 25; i++) {
    factors[i] = 0;
  }
  while (value % 2 == 0) {
    factors[0] += 1;
    value = value / 2;
  }
  for (uint16_t i = 3; i * i <= value; i = i + 2) {
    while (value % i == 0) {
      factors[indexSwitch(i)] += 1;
      value = value / i;
    }
  }
  if (value > 2) {
    factors[indexSwitch(value)] += 1;
  }
  char buff[10];
  for (uint8_t i = 0; i < 25; i++) {
    if (factors[i] != 0) {
      sprintf(buff, "%u %d ", i, factors[i]);
      lcd->WriteText(buff);
    }
  }
  return factors;
}

void removeCommonFactors(uint16_t **ptrToArray, uint8_t arrayLength) {
  uint16_t min;
  for (uint8_t i = 0; i < 25; i++) {
    min = ptrToArray[0][i];
    for (uint8_t j = 0; j < arrayLength; j++) {
      if (min > ptrToArray[j][i]) {
        min = ptrToArray[j][i];
      }
    }
    for (uint8_t k = 0; k < arrayLength; k++) {
      ptrToArray[k][i] -= min;
    }
  }
}

uint16_t deFactorize(uint16_t value) {
  switch (value) {
  case 0:
    return 2;
  case 1:
    return 3;
  case 2:
    return 5;
  case 3:
    return 7;
  case 4:
    return 11;
  case 5:
    return 13;
  case 6:
    return 17;
  case 7:
    return 19;
  case 8:
    return 23;
  case 9:
    return 29;
  case 10:
    return 31;
  case 11:
    return 37;
  case 12:
    return 41;
  case 13:
    return 43;
  case 14:
    return 47;
  case 15:
    return 53;
  case 16:
    return 59;
  case 17:
    return 61;
  case 18:
    return 67;
  case 19:
    return 71;
  case 20:
    return 73;
  case 21:
    return 79;
  case 22:
    return 83;
  case 23:
    return 89;
  case 24:
    return 97;
  default:
    return value;
  }
}
