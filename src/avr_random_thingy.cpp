#include "avr_random_thingy.h"

uint16_t randomValue(uint16_t maxInclusive) { return maxInclusive; }

void factorize(uint16_t value, HD44780 *lcd){
  uint16_t factors[10];
  char buff[2];
  buff[1] = '\0';
  while(value % 2 == 0){
    factors[0] += 1;
    buff[0] = 50;
    lcd->WriteText(buff);
    value = value / 2;
  }
  for(uint16_t i = 3; i*i <= value; i = i + 2){
    while(value % i == 0){
      buff[0] = (char)i + 48;
      lcd->WriteText(buff);
      factors[i] += 1;
      value = value / i;
    }
  }
  if(value > 2){
    buff[0] = (char)value + 48;
    lcd->WriteText(buff);
    factors[value] += 1;
  }
  // buff[0] = ((char)factors[0]) + 48;
  // lcd->WriteText(buff);
  // buff[0] = ((char)factors[3] + 48);
  // lcd->WriteText(buff);
  // buff[0] = ((char)factors[5] + 48);
  // lcd->WriteText(buff);
  // buff[0] = ((char)factors[7] + 48);
  // lcd->WriteText(buff);
}
