// timer.h
#ifndef TIMER_H
#define TIMER_H

// External reference to the global variables in timer.cpp
extern volatile uint8_t seconds;
extern volatile uint8_t minutes;

enum timeStatus {
    EVEN_MINUTE,  // 0 
    ODD_MINUTE, // 1
};

// Function declarations from timer.cpp
void timer1_init();
uint8_t currentTime();

#endif // TIMER_H
