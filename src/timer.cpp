#include <avr/io.h>
#include <avr/interrupt.h>

// Global variables
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t hours = 0;

// Timer interrupt service routine
ISR(TIMER1_COMPA_vect) {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
            hours++;
            // Reset hours after 24 to avoid overflow
            if (hours >= 24) {
                hours = 0;
            }
        }
    }
}

void timer_init() {
    TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
    OCR1A = 62499; // Set CTC compare value for 1Hz at 16MHz AVR clock, with a prescaler of 256
    TCCR1B |= (1 << CS12); // Start timer at Fcpu/256 (CS12 = 1, CS11 = 0, CS10 = 0)
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
    sei(); // Enable global interrupts
}

/************************* TIMER TEST *************************
 * Paste below loop into main() to display clock on lcd

while (1) {
    uint8_t currentSeconds = seconds;
    char time[8];
    sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
    displayText(&lcd, time);
    while (currentSeconds == seconds) {
    }
}
************************* TIMER TEST ************************/
