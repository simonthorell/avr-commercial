#include "setClock.h"

const int buttonHourPin = PD2;   // Pin for the hour button
const int buttonMinutePin = PD3; // Pin for the minute button
const int buttonSecondPin = PD4; // Pin for the second button
const int buttonSetPin = PD5;    // Pin for the set button

char timeString[9];  // Buffer to hold the formatted time string (hh:mm:ss)
int hours = 1;
int minutes = 0;
int seconds = 0;

int setClock(HD44780 lcd) {

  initializeButtons();

  // Add code to initialize your display

  while (1) {
    // Button to iterate through hours
    if (readButton(buttonHourPin)) {
      _delay_ms(50);  // Debounce delay
      hours = (hours % 24) + 1;  // Increment hours from 1 to 24
      updateDisplay();
    }

    // Button to iterate through minutes
    if (readButton(buttonMinutePin)) {
      _delay_ms(50);  // Debounce delay
      minutes = (minutes + 1) % 60;  // Increment minutes from 0 to 59
      updateDisplay();
    }

    // Button to iterate through seconds
    if (readButton(buttonSecondPin)) {
      _delay_ms(50);  // Debounce delay
      seconds = (seconds + 1) % 60;  // Increment seconds from 0 to 59
      updateDisplay();
    }

    // Button to set the time
    if (readButton(buttonSetPin)) {
      _delay_ms(50);  // Debounce delay
      // You can add code here to save the time or perform other actions
    }


  }

  return 0;
}
// simons förslags
 /*if (!(PIND & (1 << BUTTON_PIN1))) {
            // Button 1 is pressed
            // Add your code here
        }
        if (!(PIND & (1 << BUTTON_PIN2))) {
            // Button 2 is pressed
            // Add your code here
        }
        if (!(PIND & (1 << BUTTON_PIN3))) {
            // Button 3 is pressed
            // Add your code here
        }
        if (!(PIND & (1 << BUTTON_PIN4))) {
            // Button 4 is pressed
            // Add your code here
        }*/

void initializeButtons() {
  DDRD &= ~((1 << buttonHourPin) | (1 << buttonMinutePin) | (1 << buttonSecondPin) | (1 << buttonSetPin));
  PORTD |= (1 << buttonHourPin) | (1 << buttonMinutePin) | (1 << buttonSecondPin) | (1 << buttonSetPin);
}

int readButton(uint8_t pin) {
  return bit_is_clear(PIND, pin);
}

void updateDisplay() {
  snprintf(timeString, sizeof(timeString), "%02d:%02d:%02d", hours, minutes, seconds);
}