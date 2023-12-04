// #include <avr/io.h>
#include "customer_data.h"
#include "lcd_display_options.h" // For the display properties
#include <avr/pgmspace.h>

// /********************************************************************
// *                          CUSTOMER DATA
// ********************************************************************/
// // Create an array of customers and store it in PROGMEM
// const Customer customers[] PROGMEM = {
//     { "Hederlige Harrys Bilar", 5000, 3,
//         {SCROLLING, STATIC, BLINKING},
//         {
//          "K" OE "p bil hos Harry",
//          "En god bil" "aff" AE "r (f" OE "r Harry!)",
//          "Hederlige Harrys Bilar",
//         }
//     },
//     { "Farmor Ankas Pajer AB", 3000, 2,
//         {SCROLLING, STATIC},
//         {
//          "K" OE "p paj hos Farmor Anka",
//          "Skynda innan M" AA "rten " AE "tit alla pajer",
//         }
//     },
//     { "Svarte Petters Svartbyggen", 1500, 2,
//         {SCROLLING, STATIC},
//         {
//          "L" AA "t Petter bygga " AA "t dig",
//          "Bygga svart? Ring Petter"
//         }
//     },
//     { "L" AA "ngbens detektivbyr" AA, 4000, 2,
//         {STATIC, STATIC},
//         {
//          "Mysterier? Ring L" AA "ngben",
//          "L" AA "ngben fixar biffen"
//         }
//     },
//     { "IOT:s Reklambyr" AA, 1000, 1,
//         {STATIC},
//         {
//          "Synas h" AE "r? IOT:s Reklambyr" AA
//         }
//     }
// };
//

const char harryOne[] PROGMEM = "K" OE "p bil hos Harry";
const char harryTwo[] PROGMEM = "En god bilaff" AE "r (f" OE "r harry!)";
const char harryThree[] PROGMEM = "Hederlige Harrys Bilar";
const message harryText[] PROGMEM = {
    {
        SCROLLING,
        harryOne,
    },
    {
        STATIC,
        harryTwo,
    },
    {
        BLINKING,
        harryThree,
    },
};

const char ankaOne[] PROGMEM = "K" OE "p paj hos Farmor Anka";
const char ankaTwo[] PROGMEM = "Skynda innan M" AA "rten " AE "tit alla pajer";
const message ankaText[] PROGMEM = {
    {
        SCROLLING,
        ankaOne,
    },
    {
        STATIC,
        ankaTwo,
    },
};

const char svarteOne[] PROGMEM = "L" AA "t Petter bygga " AA "t dig";
const char svarteTwo[] PROGMEM = "Bygga svart? Ring Petter";
const message svarteText[] PROGMEM = {
    {
        SCROLLING,
        svarteOne,
    },
    {
        STATIC,
        svarteTwo,
    },
};

const char langOne[] PROGMEM = "Mysterier? Ring L" AA "ngben";
const char langTwo[] PROGMEM = "L" AA "ngben fixar biffen";
const message langText[] PROGMEM = {
    {
        STATIC,
        langOne,
    },
    {
        STATIC,
        langTwo,
    },
};

const char iotOne[] PROGMEM = "Synas h" AE "r? IOT:s Reklambyr" AA;
const message iotText[] PROGMEM = {
    {
        STATIC,
        iotOne,
    },
};

const Customer customers[] PROGMEM = {
    {
        "Hederlige Harrys Bilar",
        5000,
        3,
        harryText,
    },
    {
        "Farmor Ankas Pajer AB",
        3000,
        2,
        ankaText,
    },
    {
        "Svarte Petters SvartByggen",
        1500,
        2,
        svarteText,
    },
    {
        "L" AA "ngbens detektivbyr" AA,
        4000,
        2,
        langText,
    },
    {
        "IOT:s Reklambyr" AA,
        1000,
        1,
        iotText,
    },
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
