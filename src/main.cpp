#include <avr/io.h>
#include "lcd.h"
#include "lcd_display_options.h"

int main(void){
    // Create an instance of the LCD
    HD44780 lcd;

    // Initialize the LCD
    lcd.Initialize();

    // Clear the LCD screen
    lcd.Clear();

    // Define the text to be displayed
    char text1[] = "Welcome to      awesome company!";
    char text2[] = "This is a rolling commercial!";

    // The microcontroller typically runs in an infinite loop
    while (1) {
        displayText(lcd, text1);
        _delay_ms(2000);
        displayScrollingText(lcd, text2, sizeof(text2) / sizeof(char));
    }
    
    return 0;
}
