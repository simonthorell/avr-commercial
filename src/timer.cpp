#include <avr/io.h>
#include <avr/interrupt.h>

//OBS funktionen behövs ej om vi kör som main är nu

// Global variables
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;

// Timer interrupt service routine
ISR(TIMER1_COMPA_vect) {
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
    }
}

void timer1_init() {
    // [Timer initialization code here]
    TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode
    OCR1A = 15624; // Set CTC compare value for 1Hz at 1MHz AVR clock, with a prescaler of 64
    TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64
    TIMSK1 |= (1 << OCIE1A); // Enable timer compare interrupt
    sei(); // Enable global interrupts
}
