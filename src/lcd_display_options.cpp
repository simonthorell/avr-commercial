#include "lcd_display_options.h"
#include "customer_data.h"
#include "lcd.h"
#include "timer.h" // Minutes and seconds
#include "special_functions.h"
#include <avr/io.h>
#include <util/delay.h>

#define DISPLAY_TIME 20000    // Total display time in ms
#define INTERUPT_TIMER 100    // Interval for calling specialFunctions in ms

/********************************************************************
 *                   LCD DISPLAY BILLBOARD MAIN FUNCTION
 ********************************************************************/

uint8_t displayBillboard(HD44780 *lcd, char *text, int length,
                         char displayProperties) {
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

  return NOT_FOUND_ERROR;
}

/********************************************************************
 *                        LCD DISPLAY OPTIONS
 ********************************************************************/

void displayStaticText(HD44780 *lcd, char *text) {
  uint16_t duration = DISPLAY_TIME;
  displayText(lcd, text);
  
  while (duration > 0) {
    uint8_t functionExecuted = specialFunctions(lcd);
    if (functionExecuted == 1) {
      // After special function was executed, display text again. 
      displayText(lcd, text);
    }
    _delay_ms(INTERUPT_TIMER);
    duration -= INTERUPT_TIMER;
  }
}

void displayScrollingText(HD44780 *lcd, char *text, int length) {
  //TODO: NEEDS CLEANUP
  uint8_t scrollDelay = 200; // ms
  for (int i = length - 1; i < MAX_BILLBOARD_TEXT_LENGTH - 1; i++) {
    text[i] = ' ';
  }
  text[MAX_BILLBOARD_TEXT_LENGTH - 1] = '\0';
  int duration = DISPLAY_TIME;
  while (duration > 0) {
    for (int i = 0; i < length; i++) {
      displayText(lcd, text);

      for (uint16_t i = 0; i < scrollDelay; i += INTERUPT_TIMER) {
        specialFunctions(lcd); // Check if button was pressed
        _delay_ms(INTERUPT_TIMER);
        duration -= INTERUPT_TIMER;
      }

      if (duration <= 0) {
        return;
      }
      scrollText(text, length);
    }
  }
}

void displayBlinkingText(HD44780 *lcd, char *text) {
  uint16_t duration = DISPLAY_TIME;
  uint16_t blinkDelay = 500; // ms

  while (duration > 0) {
    displayText(lcd, text);
    for (uint16_t i = 0; i < blinkDelay; i += INTERUPT_TIMER) {
      specialFunctions(lcd); // Check if button was pressed
      _delay_ms(INTERUPT_TIMER);
      duration -= INTERUPT_TIMER;
    }
    lcd->Clear();
    for (uint16_t i = 0; i < blinkDelay; i += INTERUPT_TIMER) {
      specialFunctions(lcd); // Check if button was pressed
      _delay_ms(INTERUPT_TIMER);
      duration -= INTERUPT_TIMER;
    }
  }
}

/********************************************************************
 *                         HELPER FUNCTIONS
 ********************************************************************/

#define textMaxLength 32
void scrollText(char *text, int length) {
 length = length < textMaxLength ? textMaxLength : length;
  char first = text[0];
  for (int i = 0; i < length - 1; i++) {
    if(text[i + 1] == '\0'){
      text[i + i] = ' ';
    }
    text[i] = text[i + 1];
  }
  text[length - 1] = first;
  text[length] = '\0';
}

void displayText(HD44780 *lcd, char *text) {
  lcd->Clear();
  lcd->WriteText(text);
}

uint8_t getStrLen(char *text) {
  uint8_t len = 0;
  while (*(text + len) != 0) {
    len++;
  }
  len++;
  return len;
}
