#include "set_Clock.h"

const int buttonHourPin = PB0;   // Pin for the hour button
const int buttonMinutePin = PB1; // Pin for the minute button
const int buttonSecondPin = PB2; // Pin for the second button
const int buttonSetPin = PB3;    // Pin for the set button

int setClock(HD44780 *lcd) {

  
  bool done = false;
  char time[12];
  uint8_t currentSeconds = seconds;
  int hour = 0;
  int minute = 0;
  int second = 0;

  sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
  displayText(lcd, time);
  initializeButtons();
  while (1) { 
    
    

    displayText(lcd, time);

    while (currentSeconds == seconds) {

      if (readButton(buttonHourPin)) {
        _delay_ms(100);  // Debounce delay
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
        _delay_ms(100);
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
        _delay_ms(100);
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
        done = true;
      }
     

    }

    if(done){
    
    }

  }

  return 0;
}

void initializeButtons() {
  DDRB &= ~((1 << buttonHourPin) | (1 << buttonMinutePin) | (1 << buttonSecondPin) | (1 << buttonSetPin));
  PORTB |= (1 << buttonHourPin) | (1 << buttonMinutePin) | (1 << buttonSecondPin) | (1 << buttonSetPin);
}

int readButton(uint8_t pin) {
  return bit_is_clear(PINB, pin);
}