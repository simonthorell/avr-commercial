#include "special_functions.h"
#include "lcd_display_options.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h> // sprintf

// Declare global variable (Bitwise flags)
volatile uint8_t specialFunctionsFlags = 0;
// volatile uint8_t lastSecond = 0;

/********************************************************************
 *                  SPECIAL FUNCTIONS MAIN FUNCTION
 ********************************************************************/

/* 
checkButtonPressed function needs to be called within the program 
with short interwalls to check for button presses
See lcd_display_options.cpp for examples. 
*/

void checkButtonPressed(HD44780 *lcd){
    for (uint8_t i = 0; i < 100; i++) {
        _delay_ms(10);
        specialFunctions(lcd);
    }
}

/********************************************************************
 *                        BUTTON PRESSED LOGIC
 ********************************************************************/

int specialFunctions(HD44780 *lcd) {
    initializeButtons();

    // Toggle flags based on button press
    if (readButton(buttonHourPin)) {
        _delay_ms(200); // Debounce delay
        specialFunctionsFlags ^= FIRE_ALARM; // Toggle flag
    }
    if (readButton(buttonMinutePin)) {
        _delay_ms(200); // Debounce delay
        specialFunctionsFlags ^= DISPLAY_CLOCK; // Toggle flag
    }
    if (readButton(buttonSecondPin)) {
        _delay_ms(200); // Debounce delay
        specialFunctionsFlags ^= FLAG_THREE; // Toggle flag
    }
    if (readButton(buttonSetPin)) {
        _delay_ms(200); // Debounce delay
        specialFunctionsFlags ^= FLAG_FOUR; // Toggle flag
    }

    // Act based on flags
    if (specialFunctionsFlags & FIRE_ALARM) {
        fireAlarm(lcd);
        // specialFunctionsFlags &= ~FIRE_ALARM; // Optionally clear flag
    }
    if (specialFunctionsFlags & DISPLAY_CLOCK) {
        displayClock(lcd);
        // specialFunctionsFlags &= ~DISPLAY_CLOCK; // Optionally clear flag
    }
    if (specialFunctionsFlags & FLAG_THREE) {
        // Call corresponding function
        // specialFunctionsFlags &= ~FLAG_THREE; // Optionally clear flag
    }
    if (specialFunctionsFlags & FLAG_FOUR) {
        // Call corresponding function
        // specialFunctionsFlags &= ~FLAG_FOUR; // Optionally clear flag
    }

    return 0;
}

/********************************************************************
 *                        SPECIAL FUNCTIONS
 ********************************************************************/

int fireAlarm(HD44780 *lcd) {
    char alarmMessage[] = "FIRE ALARM";
    displayText(lcd, alarmMessage);

    // Wait for button press to acknowledge the alarm
    while (1) {
        if (readButton(buttonHourPin)) { // Replace 'yourButtonPin' with the actual button pin you are using
            _delay_ms(200); // Debounce delay
            specialFunctionsFlags &= ~FIRE_ALARM; // clear flag
            break; // Exit the loop if the button is pressed
        }
    }

    return 0;
}

int displayClock(HD44780 *lcd) {
    while (1) {
        uint8_t currentSeconds = seconds;
        char time[12];
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
        displayText(lcd, time);
        while (currentSeconds == seconds) {
        }
    }
    return 0;
}
