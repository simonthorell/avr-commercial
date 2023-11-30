#ifndef LCD_DISPLAY_OPTIONS_H
#define LCD_DISPLAY_OPTIONS_H

// function prototypes
void scrollText(char* text, int length);

// Display Options
void displayText(HD44780 lcd, char* text);
void displayScrollingText(HD44780 lcd, char* text, int length);

#endif // LCD_DISPLAY_OPTIONS_H
