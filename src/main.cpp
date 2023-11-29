#include <avr/io.h>
#include "lcd.h"

int main(void){
    // Create an instance of the LCD
    HD44780 lcd;

    // Initialize the LCD
    lcd.Initalize();

    // Clear the LCD screen
    lcd.Clear();

    // Define the text to be displayed
    char text[] = "Hello World!";

    // Display the text on the LCD
    lcd.WriteText(text);

    // The microcontroller typically runs in an infinite loop
    while (1) {
        // Your main program logic here
        // If you want to update the display, you can call lcd.WriteText with new text
    }
    
    return 0;
}
