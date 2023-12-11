#include "lcd_display_options.h"
#include "customer_data.h"
#include "lcd.h"
#include "timer.h" // Minutes and seconds
#include "special_functions.h"
#include <avr/io.h>
#include <util/delay.h>

#define DISPLAY_TIME 20000    // Total display time in ms
#define INTERUPT_TIMER 100    // Interval for calling specialFunctions in ms
#define BOUNCE_TIMER 300

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
  int ticks = 0;
  int elapsed_time = 0;
  int len = getStrLen(text);
  int flips = 0;
  char modifiedText[33];

  displayText(lcd, text);
  
  while (duration > 0) {
    if (len > 32 && elapsed_time >= BOUNCE_TIMER) {
        bounceSecondRow(text, modifiedText, ticks, flips);
        displayText(lcd, modifiedText);
        ticks++;
        elapsed_time = 0;
    }
    if(ticks + 32 == len){
      ticks = 0;
      flips++;
    }
    
    uint8_t functionExecuted = specialFunctions(lcd);
    if (functionExecuted == DISPLAY_FUNCTION) {
      // After special function was executed, display text again. 
      displayText(lcd, text);
    } 
    if (functionExecuted == SHOW_NEXT_BILLBOARD) {
      // Break if next billboard was requested
      return;
    }
    _delay_ms(INTERUPT_TIMER);
    duration -= INTERUPT_TIMER;
    elapsed_time += INTERUPT_TIMER;
    
  }
}

void displayScrollingText(HD44780 *lcd, char *text, int length) {
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
        uint8_t functionExecuted = specialFunctions(lcd); // Check if button was pressed
        if (functionExecuted == SHOW_NEXT_BILLBOARD) {
          // Break if next billboard was requested
          return;
        }
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
  int len = getStrLen(text);
  int flips = 1;
  char modifiedText[32];
  clipToSecondPart(text, modifiedText);
  while (duration > 0) {
    if(len > 32 && flips % 2 == 0){
      displayText(lcd, modifiedText);
      flips++;
    }else{
      displayText(lcd, text);
      flips++;
    }
    
    for (uint16_t i = 0; i < blinkDelay; i += INTERUPT_TIMER) {
      uint8_t functionExecuted = specialFunctions(lcd); // Check if button was pressed
      if (functionExecuted == SHOW_NEXT_BILLBOARD) {
        // Break if next billboard was requested
        return;
      }
      _delay_ms(INTERUPT_TIMER);
      duration -= INTERUPT_TIMER;
    }
    lcd->Clear();
    for (uint16_t i = 0; i < blinkDelay; i += INTERUPT_TIMER) {
      uint8_t functionExecuted = specialFunctions(lcd); // Check if button was pressed
      if (functionExecuted == SHOW_NEXT_BILLBOARD) {
        // Break if next billboard was requested
        return;
      }
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
      text[i + 1] = ' ';
    }
    text[i] = text[i + 1];
  }
  text[length - 1] = first;
  text[length] = '\0';
}

void bounceSecondRow(char *text, char *result, int ticks, int flips) {
  int secondRowIndex = 16;
  int len = getStrLen(text);
  int reverseLow = len - 17;
  int reverseHigh = len - 1;

    for (int i = 0; i < 16; i++) {
        result[i] = text[i];
    }

  if(flips % 2 == 0){
    for (int j = 16+ticks; j < 32+ticks; j++) {
      result[secondRowIndex] = text[j];
      secondRowIndex++;
    }
    
  }else{
    for(int i = reverseLow - ticks; i < reverseHigh - ticks; i++){
      result[secondRowIndex] = text[i];
      secondRowIndex++;
    }
  }
    result[32] = '\0';
}

void clipToSecondPart(char *text, char *result){
  int len = getStrLen(text);
  int secondRowIndex = 15;

  for (int i = 0; i < 16; i++) {
        result[i] = text[i];
    }

  for (int i = 32; i < len; i++) {
        result[secondRowIndex] = text[i];
        secondRowIndex++;
  }
  result[32] = '\0';
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
