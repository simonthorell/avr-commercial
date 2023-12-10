#ifndef LCD_DISPLAY_OPTIONS_H
#define LCD_DISPLAY_OPTIONS_H

#include "lcd.h"

// Define flags for billboard display properties
#define STATIC          0x01  // Binary: 00000001
#define SCROLLING       0x02  // Binary: 00000010
#define BLINKING        0x04  // Binary: 00000100
#define TIME_MIN_EVEN   0x08  // Binary: 00001000
#define TIME_MIN_ODD    0x10  // Binary: 00010000

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
void bounceSecondRow(char *text, char *result, int ticks, int flips);
void clipToSecondPart(char *text, char *result);
void displayText(HD44780 *lcd, char* text);
uint8_t getStrLen(char *text);

#endif // LCD_DISPLAY_OPTIONS_H
