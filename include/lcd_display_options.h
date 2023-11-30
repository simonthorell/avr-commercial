#ifndef LCD_DISPLAY_OPTIONS_H
#define LCD_DISPLAY_OPTIONS_H

#include "lcd.h"

// Define flags for billboard display properties
#define STATIC      0x00
#define SCROLLING   0x01
#define BLINKING    0x02

// Helper function prototypes
void scrollText(char* text, int length);
void displayText(HD44780 lcd, char* text);

// Display Options
void displayStaticText(HD44780 lcd, char* text);
void displayScrollingText(HD44780 lcd, char* text, int length);
void displayBlinkingText(HD44780 lcd, char* text, int duration);

#endif // LCD_DISPLAY_OPTIONS_H
