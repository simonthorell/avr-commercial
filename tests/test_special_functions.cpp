#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#ifndef BAUD
#define BAUD 9600
#endif

#define MYUBRR F_CPU/16/BAUD-1

void uart_init(unsigned int ubrr) {
    // Set baud rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_transmit(unsigned char data) {
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)));

    // Put data into buffer, sends the data
    UDR0 = data;
}

int main(void) {
    uart_init(MYUBRR);
    printf("Testing printf!\n");

    while (1) {
        uart_transmit('H');
        uart_transmit('e');
        uart_transmit('l');
        uart_transmit('l');
        uart_transmit('o');
        uart_transmit('\n');

        _delay_ms(1000);
    }

    return 0;
}
