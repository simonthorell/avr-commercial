// #include <avr/io.h>
#include "customer_data.h"
#include "lcd_display_options.h" // For the display properties
#include <avr/pgmspace.h>

#define getNumMessages(x) (sizeof(x) / sizeof(message))

// /********************************************************************
// *                          CUSTOMER DATA
// ********************************************************************/
const char harryOne[] PROGMEM = "K" OE "p bil hos Harry";
const char harryTwo[] PROGMEM = "En god bilaff" AE "r (f" OE "r harry!)";
const char harryThree[] PROGMEM = "Hederlige HarrysBilar";
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
const char ankaTwo[] PROGMEM =
    "Skynda innan    M" AA "rten " AE "tit alla pajer";
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
const char svarteTwo[] PROGMEM = "Bygga svart?    Ring Petter";
const message svarteText[] PROGMEM = {
    {
        TIME_MIN_EVEN | SCROLLING,
        svarteOne,
    },
    {
        TIME_MIN_ODD | STATIC,
        svarteTwo,
    },
};

const char langOne[] PROGMEM = "Mysterier?      Ring L" AA "ngben";
const char langTwo[] PROGMEM = "L" AA "ngben fixar   biffen";
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

const char iotOne[] PROGMEM = "Synas h" AE "r? IOT:sReklambyr" AA;
const message iotText[] PROGMEM = {
    {
        STATIC,
        iotOne,
    },
};

const char yrrolOne[] PROGMEM =
    "T-R" OE "d - f" OE "r dig som t" AE "nkt klart";
const char yrrolTwo[] PROGMEM =
    "Claes M" AA "nsson - om flickan sj" AE "lv f" AA "r v" AE "lja";
const message yrrolText[] PROGMEM = {
    {
        SCROLLING,
        yrrolOne,
    },
    {
        BLINKING,
        yrrolTwo,
    },
};

const Customer customers[] PROGMEM = {
    {
        1500,
      getNumMessages(harryText),
        harryText,
    },
    {
        3000,
        getNumMessages(ankaText),
        ankaText,
    },
    {
        1500,
        getNumMessages(svarteText),
        svarteText,
    },
    {
        4000,
        getNumMessages(langText),
        langText,
    },
    {
        1000,
        getNumMessages(iotText),
        iotText,
    },
    {
        6000,
        getNumMessages(yrrolText),
        yrrolText,
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

message getMessage(Customer *cust, uint8_t index) {
  unsigned char msgFlags;
  char *msgTxt;
  memcpy_P(&msgFlags, &cust->messageArray[index].messageFlags,
           sizeof(const unsigned char));
  memcpy_P(&msgTxt, &cust->messageArray[index].messageText,
           sizeof(const char *));
  message msg = {msgFlags, msgTxt};
  return msg;
}

constexpr uint8_t customerLength = sizeof(customers) / sizeof(Customer);
uint8_t getNumCustomers(void) { return customerLength; }
