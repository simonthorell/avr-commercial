// #include <avr/io.h>
#include <avr/pgmspace.h>
#include "customer_data.h"
#include "lcd_display_options.h" // For the display properties

/********************************************************************
*                          CUSTOMER DATA
********************************************************************/
// Create an array of customers and store it in PROGMEM
const Customer customers[] PROGMEM = {
    { "Hederlige Harrys Bilar", 5000.0,
        {SCROLLING, STATIC, BLINKING},
        {
         "K" OE "p bil hos Harry",
         "En god bil" AA "ff" AE "r (f" OE "r Harry!)",
         "Hederlige Harrys Bilar",
        }
    },
    { "Farmor Ankas Pajer AB", 3000.0,
        {SCROLLING, STATIC},
        {
         "K" OE "p paj hos Farmor Anka",
         "Skynda innan M" AA "rten " AE "tit alla pajer",
        }
    },
    { "Svarte Petters Svartbyggen", 1500.0,
        {SCROLLING, STATIC},
        {
         "L" AA "t Petter bygga " AA "t dig",
         "Bygga svart? Ring Petter"
        }
    },
    { "L" AA "ngbens detektivbyr" AA, 4000.0,
        {STATIC, STATIC},
        {
         "Mysterier? Ring L" AA "ngben",
         "L" AA "ngben fixar biffen"
        }
    },
    { "IOT:s Reklambyr" AA, 1000.0,
        {STATIC},
        {
         "Synas h" AE "r? IOT:s Reklambyr" AA
        }
    }
};

/********************************************************************
*                        GETTERS & SETTERS
********************************************************************/

Customer getCustomer(int index) {
    // Create a temporary customer
    Customer customer;
    // Copy the customer data from PROGMEM to RAM
    memcpy_P(&customer, &customers[index], sizeof(Customer));
    // Return the customer
    return customer;
}
