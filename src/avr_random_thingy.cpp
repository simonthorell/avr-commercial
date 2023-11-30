#include "avr_random_thingy.h"
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>

uint16_t randomValue(uint16_t maxInclusive) { return maxInclusive; }

//I hate this so much but it works
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

void factorize(uint16_t value, HD44780 *lcd) {
  uint16_t factors[25];
  for(uint8_t i = 0; i < 25; i++){
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
}
