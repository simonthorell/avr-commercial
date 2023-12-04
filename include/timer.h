// timer.h
#ifndef TIMER_H
#define TIMER_H

// External reference to the global variables in timer.cpp
extern volatile uint8_t seconds;
extern volatile uint8_t minutes;

// Function declarations from timer.cpp
void timer1_init();

#endif // TIMER_H
