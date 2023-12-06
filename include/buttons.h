#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>

const int buttonHourPin = PB0;   // Pin for the hour button
const int buttonMinutePin = PB1; // Pin for the minute button
const int buttonSecondPin = PB2; // Pin for the second button
const int buttonSetPin = PB3;    // Pin for the set button

void initializeButtons();
int readButton(uint8_t pin);

#endif
