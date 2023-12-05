#ifndef __avr_random_noise_h
#define __avr_random_noise_h

#include "customer_data.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE

class pseudoRandom {
public:
  pseudoRandom(void);
  pseudoRandom(uint8_t port);
  ~pseudoRandom(void);
  uint16_t getRandom(uint16_t maxInclusive);
  uint16_t getRandom(uint16_t minInclusive, uint16_t maxInclusive);
  uint8_t getRandomCustomer(uint8_t maxCustomers, uint16_t totalPayed);

private:
  uint8_t port;
  void initializeRandom(uint8_t port);
  uint16_t randomValue(void);
  uint16_t scaleNumber(uint16_t minInclusive, uint16_t maxInclusive,
                       uint16_t value);
};

#endif // !__avr_random_noise_h
