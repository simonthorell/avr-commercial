#ifndef SPECIAL_FUNCTIONS_H
#define SPECIAL_FUNCTIONS_H

#include "buttons.h"
#include "lcd.h" // HD44780 library

// Global variable (Bitwise flags)
extern volatile uint8_t specialFunctionsFlags;

// Bitwise flags
const uint8_t FIRE_ALARM = 1 << 0;     // 00000001
const uint8_t DISPLAY_CLOCK = 1 << 1;  // 00000010
const uint8_t NEXT_BILLBOARD = 1 << 2; // 00000100
const uint8_t FLAG_FOUR = 1 << 3;      // 00001000

enum SpecialFunctions {
  DISPLAY_FUNCTION = 1,
  SHOW_NEXT_BILLBOARD = 2,
};

// Core function
void initializeButtonInterrupts();

// Button pressed logic
int specialFunctions(HD44780 *lcd);

// Special functions
int fireAlarm(HD44780 *lcd);
int displayClock(HD44780 *lcd);

#endif
