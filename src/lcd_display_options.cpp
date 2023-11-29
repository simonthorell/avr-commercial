#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void scrollText(char* text, int length) {
    char first = text[0];
    for(int i = 0; i < length - 1; i++) {
        text[i] = text[i + 1];
    }
    text[length - 1] = first;
}

void displayText(HD44780 lcd, char* text) {
    lcd.Clear();
    lcd.WriteText(text);
}

void displayScrollingText(HD44780 lcd, char* text, int length) {
    for(int i = 0; i < length; i++) {
        displayText(lcd, text);
        _delay_ms(200);
        scrollText(text, length);
    }
}