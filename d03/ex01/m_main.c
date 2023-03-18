#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define UART_BAUDRATE 115200
#define MYUBRR 8 // Technically, F_CPU / (16L * UART_BAUDRATE) - 1 -> 7.68 =~ 8

#define TIMER1_PRESCALER 1024
#define TIMER1_MAX_MS 1000L * 0xFFFFL / F_CPU *TIMER1_PRESCALER

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

void timer1_launch(void)
{
    // Set timer1 to CTC mode
    TCCR1B |= (1 << WGM12);
    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // Set OCR1A to the equivalent of 2 seconds
    OCR1A = 0xFFFFUL / (TIMER1_MAX_MS / 2000);
    // Enable timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
    uart_printstr("Hello World!\r\n");
}

void uart_init(unsigned int ubrr)
{
    UBRR0H = (ubrr >> 8);
    UBRR0L = ubrr;

    // Set frame format: 8 data bits, 1 stop bit, no parity
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
    // Enable transmitter
    UCSR0B |= (1 << TXEN0);
}

int main(void)
{
    uart_init(MYUBRR);
    timer1_launch();
    
    // Enable global interrupts
    sei();

    while (1993)
    {
    }
}
