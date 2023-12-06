#include "buttons.h"

void initializeButtons() {
  DDRB &= ~((1 << buttonHourPin) | (1 << buttonMinutePin) | (1 << buttonSecondPin) | (1 << buttonSetPin));
  PORTB |= (1 << buttonHourPin) | (1 << buttonMinutePin) | (1 << buttonSecondPin) | (1 << buttonSetPin);
}

int readButton(uint8_t pin) {
  return bit_is_clear(PINB, pin);
}