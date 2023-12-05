// timer.h
#ifndef TIMER_H
#define TIMER_H

// External reference to the global variables in timer.cpp
extern volatile uint8_t seconds;
extern volatile uint8_t minutes;
extern volatile uint8_t hours;

// Function declarations from timer.cpp
void timer_init();

#endif // TIMER_H
