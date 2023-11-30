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
        displayText(lcd, customer.billboards[i]);
        _delay_ms(1000);
        
        if (!(i > 1)) {
            i++;
        } else {
            i = 0;
        }
    }
    
    return 0;
}
