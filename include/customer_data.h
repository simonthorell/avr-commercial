#ifndef CUSTOMER_DATA_H
#define CUSTOMER_DATA_H

#include <stdint.h>

// Define the number of customers
#define MAX_BILLBOARD_TEXT_LENGTH 45

// Define special characters
#define OE "\xEF"
#define AE "\xE1"
#define AA "\x08"

typedef struct {
  const unsigned char messageFlags;
  const char *messageText;
} message;

// Define a structure for customer data
typedef struct {
  uint16_t balance;        // Account balance
  uint8_t billboardsCount; // Number of billboards
  const message *messageArray;
} Customer;

// Define a function to get a customer from PROGMEM
Customer getCustomer(int index);
message getMessage(Customer *cust, uint8_t index);
uint8_t getNumCustomers(void);

#endif
