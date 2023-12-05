#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include "timer.h"
#include "set_Clock.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

#define maxCustomers 5

void displayMessage(uint8_t winner, HD44780 *lcd, pseudoRandom *rnd);  

int main(void) {
  // initialize timer (TODO: How to sync with NTP-server?)
  
  
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

  setClock(&lcd);
  timer_init();

  while (1) {
    uint8_t currentSeconds = seconds;
    char time[12];
    sprintf(time, "%02d:%02d:%02d", hours, minutes, seconds);
    displayText(&lcd, time);
    while (currentSeconds == seconds) {
    }
  }

  uint8_t lastShown = maxCustomers; // Out of bounds to start
  uint8_t winningCustomer = rnd.getRandomCustomer(maxCustomers, totalPayed);

  while (1) {
    // Making sure same customer dont get shown twice
    while (lastShown == winningCustomer) {
      winningCustomer =
          rnd.getRandomCustomer(maxCustomers, totalPayed);
    }
    lastShown = winningCustomer;

    displayMessage(winningCustomer, &lcd, &rnd);

  }
  return EXIT_SUCCESS;
}

// Display random billboard
void displayMessage(uint8_t winner, HD44780 *lcd, pseudoRandom *rnd){
  char buff[40]; //some extra padding
  Customer customer = getCustomer(winner);

  uint8_t billboardDisplayed = -1; //Out of bounds to start to not randomly get assigned 0
  while (billboardDisplayed != SUCCESS) {
    uint8_t lastBillboard = -1; // Out of bounds to start
    uint8_t randomBillboard = rnd->getRandom(customer.billboardsCount);

    if (randomBillboard != lastBillboard) {
      message custMessage = getMessage(&customer, rnd->getRandom(customer.billboardsCount - 1));
      memcpy_P(&buff, custMessage.messageText, 40);
      billboardDisplayed = displayBillboard(lcd, buff, getStrLen(buff), custMessage.messageFlags);
    }
    lastBillboard = randomBillboard; 
  }

  return;
}
