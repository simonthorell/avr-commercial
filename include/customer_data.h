#include <stdbool.h>

#ifndef CUSTOMER_DATA_H
#define CUSTOMER_DATA_H

// Define the number of customers
#define MAX_CUSTOMERS 10
#define MAX_CUSTOMER_NAME_LENGTH 30
#define MAX_BILLBOARDS 5
#define MAX_BILLBOARD_TEXT_LENGTH 45

// Define special characters
#define OE "\xEF"
#define AE "\xE1"
#define AA "\x08"

// Define a structure for customer data
struct Customer {
    char name[MAX_CUSTOMER_NAME_LENGTH];  // Customer name
    uint16_t balance;  // Account balance
    uint8_t billboardsCount;  // Number of billboards
    char displayProperties[5]; // Display properties for each billboard
    char billboards[MAX_BILLBOARDS][MAX_BILLBOARD_TEXT_LENGTH];  // Array of billboard strings
};

// Define a function to get a customer from PROGMEM
Customer getCustomer(int index);

#endif
