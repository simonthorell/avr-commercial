#include "avr_random_thingy.h"

uint16_t randomValue(uint16_t maxInclusive) { return maxInclusive; }

//Factor table
//0 = 2
//1 = 3
//2 = 5
//4 = 7
//5 = 11
//6 = 13
//7 = 17
//8 = 19
//9 = 23
//10 = 29
//11 = 31
//12 = 37
//13 = 41
//14 = 43
//15 = 47
//16 = 53
//17 = 59
//18 = 61
//19 = 67
//20 = 71
//21 = 73
//22 = 79
//23 = 83
//24 = 89
//25 = 97

void factorize(uint16_t value, HD44780 *lcd){
  uint16_t factors[10];
  char buff[2];
  buff[1] = '\0';
  while(value % 2 == 0){
    factors[0] += 1;
    value = value / 2;
  }
  for(uint16_t i = 3; i*i <= value; i = i + 2){
    while(value % i == 0){
      factors[i] += 1;
      value = value / i;
    }
  }
  if(value > 2){
    factors[value] += 1;
  }
}
