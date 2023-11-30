#ifndef CUSTOMER_DATA_H
#define CUSTOMER_DATA_H

// Define the number of customers
#define MAX_CUSTOMERS 10
#define MAX_CUSTOMER_NAME_LENGTH 20
#define MAX_BILLBOARDS 5
#define MAX_BILLBOARD_TEXT_LENGTH 35

// Define special characters
#define OE "\xEF"
#define AE "\xE1"
#define AA "\x08" //YOU NEED TO CREATE THE CHARACTER FIRST!

// Define a structure for customer data
struct Customer {
    char name[MAX_CUSTOMER_NAME_LENGTH];  // Customer name
    float balance;  // Account balance
    char displayProperties[5]; // Display properties for each billboard
    char billboards[MAX_BILLBOARDS][MAX_BILLBOARD_TEXT_LENGTH];  // Array of billboard strings
};

// Define a function to get a customer from PROGMEM
Customer getCustomer(int index);

#endif
