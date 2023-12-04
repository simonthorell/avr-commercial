#include "avr_random_noise.h"
#include "lcd.h" //FIXME: Rmove with randomTest
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

pseudoRandom::pseudoRandom(void) {
  initializeRandom();
  return;
}

// FIXME: need to figure this out
// pseudoRandom::pseudoRandom(uint8_t port) {
//   initializeRandom(port);
//   return;
// }

pseudoRandom::~pseudoRandom(void) {
  PRR ^= (1 << PRADC); // turn off the ADC
  return;
}

// FIXME: sort this PD3 shit out
// void pseudoRandom::initializeRandom(uint8_t port) {
void pseudoRandom::initializeRandom() {
  this->port = PD3;
  PRR &= ~(1 << PRADC);                    // Turn on power to the ADC
  ADMUX &= ~((1 << REFS0) | (1 << REFS1)); // set VCC as voltage reference
  ADMUX |= this->port;                      // Start pin 3
  ADCSRA |=
      ((1 << ADPS0) |
       (1 << ADPS1));    // set the speed, lower speed needed for10bit accuracy
  ADCSRA |= (1 << ADEN); // Start the ADC
  return;
}

uint16_t pseudoRandom::randomValue() {
  uint16_t rnd = 0;
  ADCSRA |= (1 << ADSC);         // set the ADSC bit
  while (ADCSRA & (1 << ADSC)) { // wait until its cleared, we have data then
    asm(""); // dirty hack to make sure the loop doesnt get optimized out
  }
  rnd = ADCL;         // read lower 8 bits
  rnd += (ADCH << 8); // read the high 2 bits
  return rnd;
}

uint16_t pseudoRandom::getRandom(uint16_t max) {
  uint16_t value = 0;
  uint16_t rnd;
  uint8_t numBytes = 2; // getNumBytes(value);
  for (uint8_t i = 0; i < numBytes * 4; i++) {
    rnd = randomValue();
    rnd = rnd & 0x3;
    value += rnd << i * 2;
  }
  value = scaleNumber(max, value);
  return value;
}

uint8_t pseudoRandom::getNumBytes(uint16_t value) {
  if (value > 0xFF) {
    return 2;
  } else if (0xFFFF >= value) {
    return 4;
  }
  return 0;
}

// off by one, it can roll 0
// FIXME: sort fix that bug before release!
uint16_t pseudoRandom::scaleNumber(uint16_t max, uint16_t value) {
  uint32_t longValue = value;
  return (((max) * (longValue + 1)) / 0xFFFF - 1) + 1;
}

// FIXME: Remove before release
void pseudoRandom::randomTest(HD44780 *lcd) {
  uint16_t rnd = 0;
  uint8_t rndLow = 0;
  uint8_t rndHigh = 0;
  char rndBuff[30];
  while (1) {
    lcd->Clear();
    lcd->GoTo(0, 0);
    rnd = getRandom(100);
    rndLow = rnd & 0xff;
    rndHigh = rnd >> 8;
    sprintf(rndBuff, "%u", rnd);
    lcd->WriteText(rndBuff);
    sprintf(rndBuff, BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN,
            BYTE_TO_BINARY(rndHigh), BYTE_TO_BINARY(rndLow));
    lcd->GoTo(0, 1);
    lcd->WriteText(rndBuff);
    _delay_ms(500);
  }
  return;
}

uint8_t pseudoRandom::getRandomCustomer(uint8_t maxcustomers, uint16_t totalPayed){
    uint16_t random = getRandom(totalPayed);
    for(uint8_t i = 0; i < 5; i++){
      Customer customer = getCustomer(i);
      if(random < customer.balance){
        return i;
      }
      random -= customer.balance;
    }
    return 0;
}
