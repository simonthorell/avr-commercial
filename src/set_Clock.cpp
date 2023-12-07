#include "set_Clock.h"
#include "buttons.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <util/delay.h>

#define debounceTime 250

volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;

void setClock(HD44780 *lcd) {

  volatile uint8_t localSeconds = 0;
  volatile uint8_t localMinutes = 0;
  volatile uint8_t localHours = 0;
  volatile uint8_t lastShownSecond = 0xFF;

  initializeButtons();

  while (1) {

    // Limit screen refresh to prevent flashing
    if (seconds != lastShownSecond) {
      lastShownSecond = seconds;
      displayTime(localHours, localMinutes, localSeconds, lcd);
    }

    // Button to iterate through hours
    if (readButton(buttonHourPin)) {
      adjustTime(24, &localHours);
      displayTime(localHours, localMinutes, localSeconds, lcd);
      _delay_ms(debounceTime);
      lastShownSecond = seconds;
    }
    // Button to iterate through minutes
    if (readButton(buttonMinutePin)) {
      adjustTime(60, &localMinutes);
      displayTime(localHours, localMinutes, localSeconds, lcd);
      _delay_ms(debounceTime);
      lastShownSecond = seconds;
    }
    // Button to iterate through seconds
    if (readButton(buttonSecondPin)) {
      adjustTime(60, &localSeconds);
      displayTime(localHours, localMinutes, localSeconds, lcd);
      _delay_ms(debounceTime);
      lastShownSecond = seconds;
    }
    // Button to set the time
    if (readButton(buttonSetPin)) {
      seconds = localSeconds;
      minutes = localMinutes;
      hours = localHours;
      return;
    }
  }
  return;
}

void displayTime(uint8_t localHours, uint8_t localMinutes, uint8_t localSeconds,
                 HD44780 *lcd) {
  char time[33];
  sprintf(time, "%16s", "Set the time" "    ");
  if (seconds % 2 == 0) {
    sprintf(time + 16,
            "%02d:%02d:%02d "
            "\x09",
            localHours, localMinutes, localSeconds);
  } else {
    sprintf(time + 16,
            "%02d:%02d:%02d "
            "\x0a"
            "\x0b",
            localHours, localMinutes, localSeconds);
  }
  displayText(lcd, time);
  return;
}

void adjustTime(uint8_t maxBeforeWrap, volatile uint8_t *valueToAdjust) {
  *valueToAdjust =
      (*valueToAdjust + 1) % maxBeforeWrap; // Increment seconds from 0 to 59
  if (*valueToAdjust >= maxBeforeWrap) {
    *valueToAdjust = 0;
  }
}
