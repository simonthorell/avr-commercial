#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcd_display_options.h"
#include "timer.h" // Minutes and seconds

#include <string.h>

#define DISPLAY_TIME 20000

/********************************************************************
*                   LCD DISPLAY BILLBOARD MAIN FUNCTION
********************************************************************/

uint8_t displayBillboard(HD44780 *lcd, char* text, int length, char displayProperties) {
    uint8_t timeStatus = currentTime();

    // Check TIME_MIN_EVEN flag
    if ((displayProperties & TIME_MIN_EVEN) && (timeStatus != EVEN_MINUTE)) {
        return TIME_ERROR;
    }

    // Check TIME_MIN_ODD flag
    if ((displayProperties & TIME_MIN_ODD) && (timeStatus != ODD_MINUTE)) {
        return TIME_ERROR;
    }

    // Check STATIC flag
    if (displayProperties & STATIC) {
        displayStaticText(lcd, text);
        return SUCCESS;
    }

    // Check BLINKING flag
    if (displayProperties & BLINKING) {
        displayBlinkingText(lcd, text);
        return SUCCESS;
    }

    // Check SCROLLING flag
    if (displayProperties & SCROLLING) {
        displayScrollingText(lcd, text, length);
        return SUCCESS;
    }

    /*** TESTING BITWISE ***/
    // displayProperties = TIME_MIN_EVEN | BLINKING;
    // char binaryStr[9];  // Buffer for binary string representation
    // for (int i = 7; i >= 0; --i) {
    //     binaryStr[7 - i] = (displayProperties & (1 << i)) ? '1' : '0';
    // }
    // binaryStr[8] = '\0';  // Null-terminate the string
    // displayStaticText(lcd, binaryStr);

    return NOT_FOUND_ERROR;
}

/********************************************************************
*                        LCD DISPLAY OPTIONS
********************************************************************/

void displayStaticText(HD44780 *lcd, char* text) {
    displayText(lcd, text);
    _delay_ms(DISPLAY_TIME);
}

void displayScrollingText(HD44780 *lcd, char* text, int length) {
    int duration = DISPLAY_TIME;
    while(duration > 0){
        for(int i = 0; i < length; i++) {
            displayText(lcd, text);
            _delay_ms(200);
            duration -= 200;
            if (duration <= 0) {
                return;
            }
            scrollText(text, length);
        }
    }
}

void displayBlinkingText(HD44780 *lcd, char* text) {
    int duration = DISPLAY_TIME;
    while(duration > 0) {
        displayText(lcd, text);
        _delay_ms(500);
        lcd->Clear();
        _delay_ms(500);
        duration -= 1000;
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
