// set_Clock.h
#ifndef SET_CLOCK_H_
#define SET_CLOCK_H_

#include "lcd.h"
#include "lcd_display_options.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int setClock(HD44780 *lcd);
void displayTime(uint8_t hours, uint8_t minutes, uint8_t seconds, HD44780 *lcd);
void adjustTime(uint8_t maxBeforeWrap, volatile uint8_t *valueToAdjust);

#endif
