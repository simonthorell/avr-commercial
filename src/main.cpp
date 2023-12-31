#include "avr_random_noise.h"    // Generate random numbers
#include "buttons.h"             // Button interrupts
#include "customer_data.h"       // Customer data
#include "lcd.h"                 // LCD class
#include "lcd_display_options.h" // Display billboards
#include "set_Clock.h"           // Set start time
#include "special_functions.h"   // Button interrupts
#include "timer.h"               // Start the timer/clock
#include <avr/io.h>              // For ISR
#include <stdint.h>              // uint8_t (NeoVIM)
#include <stdlib.h>              // std return values

/* This application is a billboard display that shows a random message
 * from a random customer. The customer is selected based on the amount
 * they have payed. The more money they have payed, the higher the
 * chance of them being selected.
 *
 * The billboards are displayed in a random order. The order is
 * determined by the random seed. The seed is generated by the
 * pseudoRandom class using the hardware to generate random noise.
 *
 * The billboards can get interrupted by showing special functions.
 * The special functions are triggered by the buttons connected to
 * the MCU.
 */

// Function declarations
int runBillboards(HD44780 *lcd, pseudoRandom *rnd);
int calculateTotalPayed(uint16_t *totalPayed);
int checkLastCustomer(uint8_t &lastShown, uint8_t &winningCustomer,
                      uint16_t totalPayed, pseudoRandom *rnd);
int displayMessage(uint8_t winner, HD44780 *lcd, pseudoRandom *rnd);

/********************************************************************
 *                          MAIN / SETUP
 ********************************************************************/

int main(void) {
  HD44780 lcd;      // Create an instance of the LCD
  pseudoRandom rnd; // Create an instance of random

  lcd.Initialize(); // Initialize the LCD
  lcd.Clear();      // Clear the LCD

  timer_init();   // Start timer/clock
  setClock(&lcd); // Set start time

  initializeButtons();          // Configure buttons as inputs
  initializeButtonInterrupts(); // Enable interrupts

  runBillboards(&lcd, &rnd); // Start the loop

  return EXIT_SUCCESS;
}

/********************************************************************
 *                      APPLICATION CORE LOOP
 ********************************************************************/

int runBillboards(HD44780 *lcd, pseudoRandom *rnd) {
  uint16_t totalPayed = 0; // Calculate total payed by all customers
  calculateTotalPayed(&totalPayed);

  uint8_t lastShown = 4; // Set index to IoT23 to avoid as first customer
  uint8_t winningCustomer =
      rnd->getRandomCustomer(getNumCustomers(), totalPayed);

  while (1) {
    checkLastCustomer(lastShown, winningCustomer, totalPayed, rnd);
    displayMessage(winningCustomer, lcd, rnd);
  }

  return SUCCESS;
}

/********************************************************************
 *                         HELPER FUNCTIONS
 ********************************************************************/

int calculateTotalPayed(uint16_t *totalPayed) {
  for (uint8_t i = 0; i < getNumCustomers(); i++) {
    Customer customer = getCustomer(i);
    *totalPayed += customer.balance;
  }
  return SUCCESS;
}

int checkLastCustomer(uint8_t &lastShown, uint8_t &winningCustomer,
                      uint16_t totalPayed, pseudoRandom *rnd) {
  while (lastShown == winningCustomer) {
    winningCustomer = rnd->getRandomCustomer(getNumCustomers(), totalPayed);
  }
  lastShown = winningCustomer;
  return SUCCESS;
}

int displayMessage(uint8_t winner, HD44780 *lcd, pseudoRandom *rnd) {
  char buff[MAX_BILLBOARD_TEXT_LENGTH];
  Customer customer = getCustomer(winner);

  uint8_t billboardDisplayed = -1;
  while (billboardDisplayed != SUCCESS) {
    static uint8_t lastBillboard = -1;
    uint8_t randomBillboard = rnd->getRandom(customer.billboardsCount);

    if (randomBillboard != lastBillboard) {
      message custMessage =
          getMessage(&customer, rnd->getRandom(customer.billboardsCount - 1));
      memcpy_P(&buff, custMessage.messageText, MAX_BILLBOARD_TEXT_LENGTH);

      billboardDisplayed = displayBillboard(lcd, buff, getStrLen(buff),
                                            custMessage.messageFlags);
    }
    lastBillboard = randomBillboard;
  }

  return SUCCESS;
}
