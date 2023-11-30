#include <avr/io.h>
#include "lcd.h"
#include "lcd_display_options.h"
#include "customer_data.h"

int main(void){
    // Create an instance of the LCD
    HD44780 lcd;
    // Initialize & clear the LCD
    lcd.Initialize();
    lcd.Clear();

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
