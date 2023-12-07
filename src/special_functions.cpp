#include "special_functions.h"
#include "buttons.h"
#include "lcd_display_options.h"
#include "timer.h"

// Declare global variable (Bitwise flags)
volatile uint8_t specialFunctionsFlags = 0;
volatile uint8_t lastSecond = 0;

/********************************************************************
 *                  SPECIAL FUNCTIONS CORE FUNCTION
 ********************************************************************/

/* 
checkButtonPressed function needs to be called within the program 
with short interwalls to check for button presses
See lcd_display_options.cpp for examples. 
*/

void checkButtonPressed(HD44780 *lcd){
    if (seconds != lastSecond) {
        specialFunctions(lcd);
    }
    lastSecond = seconds;
}

/********************************************************************
 *                        BUTTON PRESSED LOGIC
 ********************************************************************/

int specialFunctions(HD44780 *lcd) {
    initializeButtons();
    int run = 1;
    while (run) {
        if (readButton(buttonHourPin)) {
            _delay_ms(250);
            specialFunctionsFlags |= FIRE_ALARM;
        }
        if (readButton(buttonMinutePin)) {
            _delay_ms(250);
            specialFunctionsFlags |= DISPLAY_TIME;
        }
        if (readButton(buttonSecondPin)) {
            _delay_ms(250);
            specialFunctionsFlags |= FLAG_THREE;
        }
        if (readButton(buttonSetPin)) {
            _delay_ms(250);
            specialFunctionsFlags |= FLAG_FOUR;
        }

        // Check and act on each flag
        if (specialFunctionsFlags & FIRE_ALARM) {
            specialFunctionsFlags &= ~FIRE_ALARM; // Clear the flag
            fireAlarm(lcd);
            return 0; // End current process
        }
        if (specialFunctionsFlags & DISPLAY_TIME) {
            specialFunctionsFlags &= ~DISPLAY_TIME;
            displayTime(lcd);
            return 0;
        }
        if (specialFunctionsFlags & FLAG_THREE) {
            specialFunctionsFlags &= ~FLAG_THREE;
            // Call corresponding function
            return 0;
        }
        if (specialFunctionsFlags & FLAG_FOUR) {
            specialFunctionsFlags &= ~FLAG_FOUR;
            // Call corresponding function
            return 0;
        }
    }
    return 0; // ERROR
}

/********************************************************************
 *                        SPECIAL FUNCTIONS
 ********************************************************************/

int fireAlarm(HD44780 *lcd) {
    char alarmMessage[] = "FIRE ALARM";
    displayBlinkingText(lcd, alarmMessage);
    while (1) {
        checkButtonPressed(lcd); // Check for button press
        _delay_ms(500);
    }
    return 0;
}

int displayTime(HD44780 *lcd) {
    while (1) {
        uint8_t currentSeconds = seconds;
        char time[12];
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
        displayText(&lcd, time);
        while (currentSeconds == seconds) {
        }
    }
    return 0;
}