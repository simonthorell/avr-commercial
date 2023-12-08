#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// Assuming these are the definitions or prototypes of your functions and structures
#define SUCCESS 0
typedef struct {
    uint16_t balance;
} Customer;

// Mock definitions for getNumCustomers and getCustomer
uint8_t getNumCustomers() {
    return 3; // Example number of customers
}

Customer getCustomer(uint8_t index) {
    // Return mock customers with predetermined balances
    Customer customers[3] = {{100}, {200}, {300}};
    return customers[index];
}

// Function to be tested
int calculateTotalPayed(uint16_t *totalPayed) {
  for (uint8_t i = 0; i < getNumCustomers(); i++) {
    Customer customer = getCustomer(i);
    *totalPayed += customer.balance;
  }
  return SUCCESS;
}

// UART setup parameters
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// UART initialization function
void uart_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// UART transmit function
void uart_transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

// Function to transmit a string via UART
void uart_print(const char *s) {
    while (*s) {
        uart_transmit(*s++);
    }
}

// Test function
void test_calculateTotalPayed() {
    uint16_t totalPayed = 0;
    int result = calculateTotalPayed(&totalPayed);

    if (result == SUCCESS && totalPayed == 600) {
        uart_print("Test passed!\n");
    } else {
        uart_print("Test failed!\n");
    }
}

int main(void) {
    uart_init(MYUBRR);
    test_calculateTotalPayed();
    // Additional tests can be added here
    while(1) {
        // Infinite loop to prevent the AVR from resetting after test completion
        _delay_ms(1000);
    }
    return 0;
}
