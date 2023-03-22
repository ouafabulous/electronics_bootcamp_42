#include "uart.h"

void uart_init(void)
{
    unsigned int ubrr = MYUBRR;

    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    // Enable receiver and transmitter
    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
}

void uart_tx(char c)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    // Put data into buffer, sends the data
    UDR0 = c;
}

void uart_printstr(const char *str)
{
    while (*str)
        uart_tx(*str++);
}

char uart_rx(void)
{
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // Get and return received data from buffer
    return UDR0;
}

void uart_printnb(unsigned int nb)
{
    if (nb >= 10)
        uart_printnb(nb / 10);
    uart_tx(nb % 10 + '0');
}

void uart_printnb_hex(unsigned int nb)
{
    if (nb >= 16)
        uart_printnb_hex(nb / 16);
    uart_tx(BASE_16[nb % 16]);
}

void uart_printnb_bin(unsigned int nb)
{
    for (int i = 0; i < 8; i++)
    {
        if (nb & (1 << (7 - i)))
            uart_tx('1');
        else
            uart_tx('0');
    }
}