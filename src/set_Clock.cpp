#include "set_Clock.h"
#include "buttons.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <util/delay.h>

#define debounceTime 250

volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;

int setClock(HD44780 *lcd) {

  volatile uint8_t localSeconds = 0;
  volatile uint8_t localMinutes = 0;
  volatile uint8_t localHours = 0;
  volatile uint8_t lastShownSecond = 0xFF;

  initializeButtons();

  int run = 1;
  while (run) {

    if (seconds != lastShownSecond) {
      lastShownSecond = seconds;
      displayTime(localHours, localMinutes, localSeconds, lcd);
    }

    if (readButton(buttonHourPin)) {
      localHours = (localHours % 24) + 1; // Increment hours from 1 to 24
      if (localHours >= 24) {
        localHours = 0;
      }
      displayTime(localHours, localMinutes, localSeconds, lcd);
      _delay_ms(debounceTime);
      lastShownSecond = seconds;
    }
    // Button to iterate through minutes
    if (readButton(buttonMinutePin)) {
      localMinutes = (localMinutes + 1) % 60; // Increment minutes from 0 to 59
      if (localMinutes >= 60) {
        localMinutes = 0;
      }
      displayTime(localHours, localMinutes, localSeconds, lcd);
      _delay_ms(debounceTime);
      lastShownSecond = seconds;
    }
    // Button to iterate through seconds
    if (readButton(buttonSecondPin)) {
      localSeconds = (localSeconds + 1) % 60; // Increment seconds from 0 to 59
      if (localSeconds >= 60) {
        localSeconds = 0;
      }
      displayTime(localHours, localMinutes, localSeconds, lcd);
      _delay_ms(debounceTime);
      lastShownSecond = seconds;
    }
    // Button to set the time
    if (readButton(buttonSetPin)) {
      // _delay_ms(50);
      seconds = localSeconds;
      minutes = localMinutes;
      hours = localHours;
      return 0;
    }
  }
  return 0;
}

void displayTime(uint8_t localHours, uint8_t localMinutes, uint8_t localSeconds,
                 HD44780 *lcd) {
  char time[15];
  if (seconds % 2 == 0) {
    sprintf(time,
            "%02d:%02d:%02d "
            "\x09",
            localHours, localMinutes, localSeconds);
  } else {
    sprintf(time,
            "%02d:%02d:%02d "
            "\x0a"
            "\x0b",
            localHours, localMinutes, localSeconds);
  }
  displayText(lcd, time);
  return;
}
