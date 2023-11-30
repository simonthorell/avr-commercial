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

    int i = 0;
    while(1) {
        // LOOP FOR TESTING
        Customer customer = getCustomer(i);

        if(customer.displayProperties[i] == SCROLLING) {
            displayScrollingText(lcd, customer.billboards[i], sizeof(customer.billboards[i]));
        } else if (customer.displayProperties[i] == STATIC) {
            displayStaticText(lcd, customer.billboards[i]);
        } else if (customer.displayProperties[i] == BLINKING) {
            displayBlinkingText(lcd, customer.billboards[i], 5);
        } else {
            continue;
        }

        if (!(i > 1)) {i++;} else {i=0;}
    }
    
    return 0;
}
