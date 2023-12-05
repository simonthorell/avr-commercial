#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcd_display_options.h"
#include "timer.h" // Minutes and seconds

/********************************************************************
*                   LCD DISPLAY BILLBOARD MAIN FUNCTION
********************************************************************/

uint8_t displayBillboard(HD44780 *lcd, char* text, int length, char displayProperties) {
    uint8_t timeStatus = currentTime();
    uint8_t test = currentTime();

    switch(displayProperties) {
        case TIME_MIN_EVEN:
            if(timeStatus != EVEN_MINUTE){
                return TIME_ERROR;
            }
            break;
        case TIME_MIN_ODD:
            if(test != EVEN_MINUTE){
                return TIME_ERROR;
            }
            break;
        case STATIC:
            displayStaticText(lcd, text);
            return SUCCESS;
            break;
        case BLINKING:
            displayBlinkingText(lcd, text);
            return SUCCESS;
            break;
        case SCROLLING:
            displayScrollingText(lcd, text, length);
            return SUCCESS;
            break;
        default: // Fallback to static
            displayStaticText(lcd, text);
            return SUCCESS;
            break;
    }
    
    return NOT_FOUND_ERROR;
}

/********************************************************************
*                        LCD DISPLAY OPTIONS
********************************************************************/

void displayStaticText(HD44780 *lcd, char* text) {
    displayText(lcd, text);
    _delay_ms(3000);
}

void displayScrollingText(HD44780 *lcd, char* text, int length) {
    for(int i = 0; i < length; i++) {
        displayText(lcd, text);
        _delay_ms(200);
        scrollText(text, length);
    }
}

void displayBlinkingText(HD44780 *lcd, char* text) {
    int duration = 5; // seconds
    for(int i = 0; i < duration; i++) {
        displayText(lcd, text);
        _delay_ms(500);
        lcd->Clear();
        _delay_ms(500);
    }
}

/********************************************************************
*                         HELPER FUNCTIONS
********************************************************************/

void scrollText(char* text, int length) {
    char first = text[0];
    for(int i = 0; i < length - 1; i++) {
        text[i] = text[i + 1];
    }
    text[length - 1] = first;
}

void displayText(HD44780 *lcd, char* text) {
    lcd->Clear();
    lcd->WriteText(text);
}

uint8_t getStrLen(char *text){
  uint8_t len = 0;
  while(*(text + len) != 0 ){
    len++;
  }
  len++;
  return len;
}
