#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include "timer.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdlib.h>
#include <util/delay.h>

void displayMessage(uint8_t winner, HD44780 *lcd, pseudoRandom *rnd);

int main(void) {
  // initialize timer (TODO: How to sync with NTP-server?)
  timer_init();

  // Create an instance of the LCD and random
  HD44780 lcd;
  pseudoRandom rnd;

  uint16_t totalPayed = 0;
  for (uint8_t i = 0; i < getNumCustomers(); i++) {
    Customer customer = getCustomer(i);
    totalPayed += customer.balance;
  }

  // Initialize & clear the LCD
  lcd.Initialize();
  lcd.Clear();

  uint8_t lastShown = getNumCustomers(); // Out of bounds to start
  uint8_t winningCustomer =
      rnd.getRandomCustomer(getNumCustomers(), totalPayed);

  while (1) {
    // Making sure same customer dont get shown twice
    while (lastShown == winningCustomer) {
      winningCustomer = rnd.getRandomCustomer(getNumCustomers(), totalPayed);
    }
    lastShown = winningCustomer;

    displayMessage(winningCustomer, &lcd, &rnd);
  }
  return EXIT_SUCCESS;
}

// Display random billboard
void displayMessage(uint8_t winner, HD44780 *lcd, pseudoRandom *rnd) {
  char buff[40]; // some extra padding
  Customer customer = getCustomer(winner);

  uint8_t billboardDisplayed =
      -1; // Out of bounds to start to not randomly get assigned 0
  while (billboardDisplayed != SUCCESS) {
    uint8_t lastBillboard = -1; // Out of bounds to start
    uint8_t randomBillboard = rnd->getRandom(customer.billboardsCount);

    if (randomBillboard != lastBillboard) {
      message custMessage =
          getMessage(&customer, rnd->getRandom(customer.billboardsCount - 1));
      memcpy_P(&buff, custMessage.messageText, 40);
      billboardDisplayed = displayBillboard(lcd, buff, getStrLen(buff),
                                            custMessage.messageFlags);
    }
    lastBillboard = randomBillboard;
  }

  return;
}
