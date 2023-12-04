#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include "timer.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

#define maxCustomers 5

int main(void) {
  // initialize timer (TODO: How to sync with NTP-server?)
  timer1_init();

  // Create an instance of the LCD and random
  HD44780 lcd;
  pseudoRandom rnd;

  uint16_t totalPayed = 0;
  // FIXME: We should probably keep track of how many customers we have in total
  for (uint8_t i = 0; i < maxCustomers; i++) {
    Customer customer = getCustomer(i);
    totalPayed += customer.balance;
  }

  // Initialize & clear the LCD
  lcd.Initialize();
  lcd.Clear();

  uint8_t lastShown = maxCustomers; // Out of bounds to start
  uint8_t winningCustomer = rnd.getRandomCustomer(maxCustomers, totalPayed);

  char buff[33];
  while (1) {
    // Making sure same dont get shown twice
    while (lastShown == winningCustomer) {
      winningCustomer =
          rnd.getRandomCustomer(0, maxCustomers, totalPayed, &lcd);
    }

    lastShown = winningCustomer;

    // should move this into its own function, so many memcopies
    Customer customer = getCustomer(winningCustomer);
    message custMessage = {0, nullptr};
    uint16_t rndMsg = rnd.getRandom(0, customer.billboardsCount - 1);
    memcpy_P(&custMessage, &customer.messageArray[rndMsg], sizeof(message));

    memcpy_P(&buff, custMessage.messageText, 32);
    displayBillboard(&lcd, buff, sizeof(buff), custMessage.messageFlags);
  }

  return EXIT_SUCCESS;
}
