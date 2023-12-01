#include "avr_random_noise.h"
#include "customer_data.h"
#include "lcd.h"
#include "lcd_display_options.h"
#include <avr/io.h>
#include <stdint.h> //So I dont get all the uint errors, just for my IDE
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Create an instance of the LCD
  HD44780 lcd;

  // Initialize & clear the LCD
  lcd.Initialize();
  lcd.Clear();
  initializeRandom();
  randomTest(&lcd); //runs a demo random function loop

    while(1) {
        // LOOP THROUGH ALL CUSTOMERS FOR TESTING
        for (int customerIndex = 0; customerIndex < 5; customerIndex++) {
            Customer customer = getCustomer(customerIndex);

            for (int billboardIndex = 0; billboardIndex < 5; billboardIndex++) {
                if (customer.displayProperties[billboardIndex] == SCROLLING) {
                    displayScrollingText(&lcd, customer.billboards[billboardIndex], sizeof(customer.billboards[billboardIndex]));
                } else if (customer.displayProperties[billboardIndex] == STATIC) {
                    displayStaticText(&lcd, customer.billboards[billboardIndex]);
                } else if (customer.displayProperties[billboardIndex] == BLINKING) {
                    displayBlinkingText(&lcd, customer.billboards[billboardIndex], 5);
                } else {
                    continue;
                }
            }
        }
    }
    return 0;
}
