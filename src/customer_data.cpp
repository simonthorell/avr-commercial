#include <avr/io.h>
#include <avr/pgmspace.h>
#include "customer_data.h"

// Create an array of customers and store it in PROGMEM
const Customer customers[] PROGMEM = {
    { "Customer1", 1000.0, {"Billboard 1", "Billboard 2", "Billboard 3", "Billboard 4", "Billboard 5"},
    {SCROLLING | BLINKING, SCROLLING, BLINKING, 0, SCROLLING} },
    { "Customer2", 1500.0, {"Billboard A", "Billboard B", "Billboard C", "Billboard D", "Billboard E"},
    {BLINKING, SCROLLING | BLINKING, 0, 0, SCROLLING} },
    { "Customer3", 2000.0, {"Billboard A1", "Billboard B2", "Billboard C3", "Billboard D4", "Billboard E5"},
    {BLINKING, SCROLLING | BLINKING, 0, 0, SCROLLING} },
};

Customer getCustomer(int index) {
    // Create a temporary customer
    Customer customer;
    // Copy the customer data from PROGMEM to RAM
    memcpy_P(&customer, &customers[index], sizeof(Customer));
    // Return the customer
    return customer;
}