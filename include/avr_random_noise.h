#ifndef __avr_random_noise_h
#define __avr_random_noise_h

#include "customer_data.h"
#include "lcd.h" //FIXME: Remove when randomTest is gone
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE

// Only here for debug purposes, lets you print out the binary format
// FIXME: Remove when randomTest is gone
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                   \
  ((byte) & 0x80 ? '1' : '0'), ((byte) & 0x40 ? '1' : '0'),                    \
      ((byte) & 0x20 ? '1' : '0'), ((byte) & 0x10 ? '1' : '0'),                \
      ((byte) & 0x08 ? '1' : '0'), ((byte) & 0x04 ? '1' : '0'),                \
      ((byte) & 0x02 ? '1' : '0'), ((byte) & 0x01 ? '1' : '0')

class pseudoRandom {
public:
  pseudoRandom(void);
  pseudoRandom(uint8_t port);
  ~pseudoRandom(void);
  uint16_t getRandom(uint16_t maxInclusive);
  uint16_t getRandom(uint16_t minInclusive, uint16_t maxInclusive);
  void randomTest(HD44780 *lcd); // FIXME: Remove before release
  uint8_t getRandomCustomer(uint8_t maxCustomers, uint16_t totalPayed);
  uint8_t getRandomCustomer(uint8_t minCustomers, uint8_t maxCustomers, uint16_t totalPayed);

private:
  uint8_t port;
  void initializeRandom(uint8_t port);
  uint16_t randomValue(void);
  uint16_t scaleNumber(uint16_t minInclusive, uint16_t maxInclusive, uint16_t value);
};

#endif // !__avr_random_noise_h
