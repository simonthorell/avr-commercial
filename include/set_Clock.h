// set_Clock.h
#ifndef SET_CLOCK_H_
#define SET_CLOCK_H_

#include <avr/io.h>
#include <util/delay.h>

int setClock(HD44780 *lcd);
void initializeButtons();
int readButton(uint8_t pin);

#endif
