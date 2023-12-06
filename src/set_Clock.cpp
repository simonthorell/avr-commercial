#include "set_Clock.h"
#include "buttons.h"

volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;

int setClock(HD44780 *lcd) {

  initializeButtons();

  int run = 1;
  while (run) {

  uint8_t currentSeconds = seconds;
    char time[12];
    sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
    displayText(lcd, time);

    while (currentSeconds == seconds) {
      if (readButton(buttonHourPin)) {
        _delay_ms(250);  // Debounce delay
        hours = (hours % 24) + 1;  // Increment hours from 1 to 24
        if(hours > 24){
          hours = 0;
        }
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
        displayText(lcd, time);
        break;
      }
      // Button to iterate through minutes
      if (readButton(buttonMinutePin)) {
        _delay_ms(250);
        minutes = (minutes + 1) % 60;  // Increment minutes from 0 to 59
        if(minutes > 60){
          minutes = 0;
        }
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
        displayText(lcd, time);
        break;
      }
      // Button to iterate through seconds
      if (readButton(buttonSecondPin)) {
        _delay_ms(250);
        seconds = (seconds + 1) % 60;  // Increment seconds from 0 to 59
        if(seconds > 60){
          seconds = 0;
        }
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
        displayText(lcd, time);
        break;
      }
      // Button to set the time
      if (readButton(buttonSetPin)) {
        _delay_ms(50);
        return 0;
      }

    }

  }

  return 0;
}
