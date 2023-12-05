// setClock.h
#ifndef SETCLOCK_H_
#define SETCLOCK_H_

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int setClock(HD44780 lcd)
void initializeButtons();
int readButton(uint8_t pin);
void updateDisplay();

#endif