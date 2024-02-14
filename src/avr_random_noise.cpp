#include "avr_random_noise.h"
#include "customer_data.h"
#include <avr/io.h>

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
  ADMUX &= ~(1 << ADLAR);                  // Make sure we are in 10bit mode
  ADCSRA &=
      ~((1 << ADPS0) | (1 << ADPS1) |
        (1 << ADPS2));   // Clear the speed division bits for maximum SPEEEEEED
  ADCSRA |= (1 << ADEN); // Start the ADC
  return;
}

uint8_t pseudoRandom::randomValue() {
  uint8_t rnd;
  ADCSRA |= (1 << ADSC);         // set the ADSC bit to start ADC conversion
  while (ADCSRA & (1 << ADSC)) { // wait until its cleared, we have data then
    asm(""); // dirty hack to make sure the loop doesnt get optimized out
  }
  rnd = ADCL; // read lower 8 bits
  // discarding high bytes anyway
  return rnd;
}

uint16_t pseudoRandom::getRandom(uint16_t maxInclusive) {
  ADMUX |= this->port;
  uint16_t value = 0;
  uint16_t rnd;
  for (uint8_t i = 0; i < 8; i++) {
    rnd = randomValue();
    rnd = rnd & 0x3;
    value += rnd << i * 2;
  }
  ADMUX ^= this->port;
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

uint8_t pseudoRandom::getRandomCustomer(uint8_t maxCustomers,
                                        uint16_t totalPayed) {
  uint16_t random = getRandom(0, totalPayed - 1);
  for (uint8_t i = 0; i < maxCustomers; i++) {
    Customer customer = getCustomer(i);
    if (random < customer.balance) {
      return i;
    }
    random -= customer.balance;
  }
  return 0;
}
