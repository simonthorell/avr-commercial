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
        // Do nothing! :)
        Customer customer = getCustomer(i);

        if(customer.displayProperties[i] == SCROLLING) {
            lcd.Clear();
            displayScrollingText(lcd, customer.billboards[i], sizeof(customer.billboards[i]));
            _delay_ms(1000);
        } else if (customer.displayProperties[i] == STATIC) {
            lcd.Clear();
            displayText(lcd, customer.billboards[i]);
            _delay_ms(3000);
        } else if (customer.displayProperties[i] == BLINKING) {
            lcd.Clear();
            displayText(lcd, customer.billboards[i]);
            _delay_ms(500);
            lcd.Clear();
            _delay_ms(500);
            displayText(lcd, customer.billboards[i]);
            _delay_ms(500);
            lcd.Clear();
            _delay_ms(500);
            displayText(lcd, customer.billboards[i]);
            _delay_ms(500);
            lcd.Clear();
            _delay_ms(500);
            displayText(lcd, customer.billboards[i]);
        } else {
            continue;
        }

        if (!(i > 1)) {
            i++;
        } else {
            i = 0;
        }
    }
    
    return 0;
}
