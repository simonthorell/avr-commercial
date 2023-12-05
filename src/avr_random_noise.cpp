#include "avr_random_noise.h"
#include "lcd.h" //FIXME: Rmove with randomTest
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

pseudoRandom::pseudoRandom(void) {
  initializeRandom(3);
  return;
}

pseudoRandom::pseudoRandom(uint8_t port) {
  initializeRandom(port);
  return;
}

pseudoRandom::~pseudoRandom(void) {
  PRR ^= (1 << PRADC); // turn off the ADC
  return;
}

void pseudoRandom::initializeRandom(uint8_t port) {
  this->port = port;
  PRR &= ~(1 << PRADC);                    // Turn on power to the ADC
  ADMUX &= ~((1 << REFS0) | (1 << REFS1)); // set VCC as voltage reference
  ADMUX |= this->port;                     // Start selected pin
  ADCSRA &=
      ~((1 << ADPS0) | (1 << ADPS1) |
        (1 << ADPS2));   // Clear the speed division bits for maximum SPEEEEEED
  ADCSRA |= (1 << ADEN); // Start the ADC
  return;
}

uint16_t pseudoRandom::randomValue() {
  uint16_t rnd = 0;
  ADCSRA |= (1 << ADSC);         // set the ADSC bit to start ADC conversion
  while (ADCSRA & (1 << ADSC)) { // wait until its cleared, we have data then
    asm(""); // dirty hack to make sure the loop doesnt get optimized out
  }
  rnd = ADCL;         // read lower 8 bits
  rnd += (ADCH << 8); // read the high 2 bits
  return rnd;
}

uint16_t pseudoRandom::getRandom(uint16_t maxInclusive) {
  uint16_t value = 0;
  uint16_t rnd;
  for (uint8_t i = 0; i < 8; i++) {
    rnd = randomValue();
    rnd = rnd & 0x3;
    value += rnd << i * 2;
  }
  value = scaleNumber(0, maxInclusive, value);
  return value;
}

uint16_t pseudoRandom::getRandom(uint16_t minInclusive, uint16_t maxInclusive) {
  uint16_t value = 0;
  uint16_t rnd;
  for (uint8_t i = 0; i < 8; i++) {
    rnd = randomValue();
    rnd = rnd & 0x3;
    value += rnd << i * 2;
  }
  value = scaleNumber(minInclusive, maxInclusive, value);
  return value;
}

uint16_t pseudoRandom::scaleNumber(uint16_t minInclusive, uint16_t maxInclusive,
                                   uint16_t value) {
  double dvalue = value;
  dvalue = (((maxInclusive - minInclusive) * (dvalue - minInclusive)) /
            (0xFFFF - 0)) +
           minInclusive;
  dvalue += 0.5;
  return (uint16_t)dvalue;
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
    rnd = getRandom(2, 15235);
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

uint8_t pseudoRandom::getRandomCustomer(uint8_t maxCustomers,
                                        uint16_t totalPayed) {
  uint16_t random = getRandom(0, totalPayed);
  for (uint8_t i = 0; i < maxCustomers; i++) {
    Customer customer = getCustomer(i);
    if (random < customer.balance) {
      return i;
    }
    random -= customer.balance;
  }
  return 0;
}

uint8_t pseudoRandom::getRandomCustomer(uint8_t maxCustomers,
                                        uint16_t totalPayed, HD44780 *lcd) {
  uint16_t random = getRandom(0, totalPayed);
  // FIXME: Remove before release
  char buff[30];
  lcd->Clear();
  sprintf(buff, "%u %u %u", random, totalPayed, maxCustomers);
  lcd->WriteText(buff);
  _delay_ms(2000);
  // FIXME_END
  for (uint8_t i = 0; i < maxCustomers; i++) {
    Customer customer = getCustomer(i);
    if (random < customer.balance) {
      return i;
    }
    random -= customer.balance;
    // FIXME: Remove before release
    lcd->Clear();
    sprintf(buff, "%u %u", random, i);
    lcd->WriteText(buff);
    _delay_ms(1000);
    // FIXME_END
  }
  return 0;
}
