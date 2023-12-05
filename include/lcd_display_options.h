#ifndef LCD_DISPLAY_OPTIONS_H
#define LCD_DISPLAY_OPTIONS_H

#include "lcd.h"

// Define flags for billboard display properties
#define STATIC          0x00
#define SCROLLING       0x01
#define BLINKING        0x02
#define TIME_MIN_EVEN   0x03
#define TIME_MIN_ODD    0x04

enum displayStatus {
    SUCCESS,  // 0 
    TIME_ERROR, // 1
    NOT_FOUND_ERROR // 2
};

// Main function prototype
uint8_t displayBillboard(HD44780 *lcd, char* text, int length, char displayProperties);

// Display Options
void displayStaticText(HD44780 *lcd, char* text);
void displayScrollingText(HD44780 *lcd, char* text, int length);
void displayBlinkingText(HD44780 *lcd, char* text);

// Helper function prototypes
void scrollText(char* text, int length);
void displayText(HD44780 *lcd, char* text);
uint8_t getStrLen(char *text);

#endif // LCD_DISPLAY_OPTIONS_H
