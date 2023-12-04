#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

#define maxCustomers 5

int main(void) {
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
  uint8_t winningCustomer = rnd.getRandomCustomer(maxCustomers - 1, totalPayed);

  while (1) {

    //Making sure same dont get shown twice
    while (lastShown == winningCustomer) {
      //upper bound is inclusive so maxCustomers - 1
      winningCustomer = rnd.getRandomCustomer(maxCustomers - 1, totalPayed);
    }

    lastShown = winningCustomer;

    Customer customer = getCustomer(winningCustomer);

    displayStaticText(&lcd, customer.billboards[0]);

    _delay_ms(5000);

    // LOOP THROUGH ALL CUSTOMERS FOR TESTING
    // for (int customerIndex = 0; customerIndex < 5; customerIndex++) {
    //     Customer customer = getCustomer(customerIndex);
    //
    //     for (int billboardIndex = 0; billboardIndex < 5; billboardIndex++) {
    //         if (customer.displayProperties[billboardIndex] == SCROLLING) {
    //             displayScrollingText(&lcd,
    //             customer.billboards[billboardIndex],
    //             sizeof(customer.billboards[billboardIndex]));
    //         } else if (customer.displayProperties[billboardIndex] == STATIC)
    //         {
    //             displayStaticText(&lcd, customer.billboards[billboardIndex]);
    //         } else if (customer.displayProperties[billboardIndex] ==
    //         BLINKING) {
    //             displayBlinkingText(&lcd,
    //             customer.billboards[billboardIndex], 5);
    //         } else {
    //             continue;
    //         }
    //     }
    // }
  }
  return 0;
}
