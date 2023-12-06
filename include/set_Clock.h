// set_Clock.h
#ifndef SET_CLOCK_H_
#define SET_CLOCK_H_

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include <stdio.h>
#include "lcd_display_options.h"

int setClock(HD44780 *lcd);

#endif
