#ifndef SPECIAL_FUNCTIONS_H
#define SPECIAL_FUNCTIONS_H

/* 
These functions depend on a separate timer 
interupt (ISR) to check for button presses. 
See timer.h and timer.cpp for more information
*/

#include <avr/io.h>
#include <util/delay.h>
#include "buttons.h"

#include "lcd.h" // HD44780 library

// Global variable (Bitwise flags)
extern volatile uint8_t specialFunctionsFlags;

// Bitwise flags
const uint8_t FIRE_ALARM = 1 << 0;    // 00000001
const uint8_t DISPLAY_CLOCK = 1 << 1;  // 00000010
const uint8_t FLAG_THREE = 1 << 2;  // 00000100
const uint8_t FLAG_FOUR = 1 << 3;     // 00001000

// Core function
void checkButtonPressed(HD44780 *lcd);

// Button pressed logic
int specialFunctions(HD44780 *lcd);

// Special functions
int fireAlarm(HD44780 *lcd);
int displayClock(HD44780 *lcd);

#endif
