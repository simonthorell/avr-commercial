#include "special_functions.h"
#include "lcd_display_options.h"
#include "timer.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>              // sprintf
#include <avr/interrupt.h>      // For ISR

/* 
In main.cpp, call initializeButtonInterrupts() to enable interrupts.
Also call initialzeButtons() from 'buttons.h' to configure the buttons 
as inputs.

In keep calling specialFunctions() to execute functions triggered by
the button presses. The functions are executed in the order they are
called.
*/

// Declare global variable (Bitwise flags)
volatile uint8_t specialFunctionsFlags = 0;

#define BUTTON_DEBOUNCE_TIME 250 // ms

// ISR for button presses
ISR(PCINT0_vect) {
    // Using XOR to toggle the functions on/off
    if (readButton(buttonHourPin)) {
        _delay_ms(BUTTON_DEBOUNCE_TIME);
        specialFunctionsFlags ^= FIRE_ALARM;
    }
    if (readButton(buttonMinutePin)) {
        _delay_ms(BUTTON_DEBOUNCE_TIME);
        specialFunctionsFlags ^= DISPLAY_CLOCK;
    }
    if (readButton(buttonSecondPin)) {
        _delay_ms(BUTTON_DEBOUNCE_TIME);
        specialFunctionsFlags ^= NEXT_BILLBOARD;
    }
    if (readButton(buttonSetPin)) {
        _delay_ms(BUTTON_DEBOUNCE_TIME);
        specialFunctionsFlags ^= FLAG_FOUR;
    }
}

/********************************************************************
 *                    INITIALIZE BUTTON INTERRUPTS
 ********************************************************************/

// Configure interrupts for buttons
void initializeButtonInterrupts() {
    // Enable pin change interrupt for the group including PB0-PB3
    PCICR |= (1 << PCIE0);
    // Enable interrupts for PB0 to PB3
    PCMSK0 |= (1 << PCINT0) | (1 << PCINT1) | (1 << PCINT2) | (1 << PCINT3); 
    // Enable global interrupts
    sei();
}

/********************************************************************
 *                        BUTTON PRESSED LOGIC
 ********************************************************************/

int specialFunctions(HD44780 *lcd) {
    // Act based on flags
    if (specialFunctionsFlags & FIRE_ALARM) {
        fireAlarm(lcd);
        return DISPLAY_FUNCTION;
    }
    if (specialFunctionsFlags & DISPLAY_CLOCK) {
        displayClock(lcd);
        return DISPLAY_FUNCTION;
    }
    if (specialFunctionsFlags & NEXT_BILLBOARD) {
        specialFunctionsFlags ^= NEXT_BILLBOARD;
        return SHOW_NEXT_BILLBOARD;
    }
    // ... TODO: Add more special functions here
    return 0;
}

/********************************************************************
 *                        SPECIAL FUNCTIONS
 ********************************************************************/

int fireAlarm(HD44780 *lcd) {
    char alarmMessage[] = "FIRE ALARM!";
    char alarmOffMessage[] = "FIRE IS OVER!";
    displayText(lcd, alarmMessage);
    while (FIRE_ALARM & specialFunctionsFlags) {
        // Wait for button press handled by ISR
    }
    displayText(lcd, alarmOffMessage);
    _delay_ms(2000);
    return 0;
}

int displayClock(HD44780 *lcd) {
    while (DISPLAY_CLOCK & specialFunctionsFlags) {
        uint8_t currentSeconds = seconds;
        char time[12];
        sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
        displayText(lcd, time);
        while (currentSeconds == seconds) {
            // Wait for next second
            if (FIRE_ALARM & specialFunctionsFlags) {
                // break if button pressed
                return 0;
            }
         _delay_ms(10);
        }
    }
    return 0;
}
