#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// #define F_CPU 16000000UL
#define UART_BAUDRATE 115200
#define TIMER1_PRESCALER 1024
#define FREQ_CPU 16000000L
#define TIME_TO_FILL_TIMER (1000L * 0xFFFFL / FREQ_CPU) * TIMER1_PRESCALER 

void uart_init() {
  // Configure baud rate
  // uint16_t ubrr = F_CPU / 16 / UART_BAUDRATE - 1;
  uint16_t ubrr = 8;
  UBRR0H = ubrr >> 8;
  UBRR0L = ubrr;

  // Enable UART transmitter
  UCSR0B |= (1 << TXEN0) | (1<<RXCIE0);
  UCSR0B |= (1 << RXEN0);

  // Set frame format: 8 data bits, no parity, 1 stop bit
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char data) {
  // Wait for the UART transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)));

  // Transmit the data
  UDR0 = data;
}

char uart_rx() {
  // Wait for the UART transmit buffer to be empty
while (!(UCSR0A & (1 << RXC0)));

  // Transmit the data
  return (UDR0);
}

// void uart_printstr(const char* str){
//     while (*str) {
//         uart_tx(*str++);
//     }
// }


// void    timer1_launcher(void)
// {
//     // Set timer1 to CTC mode
//     TCCR1B |= (1 << WGM12);
//     // Set prescaler to 1024
//     TCCR1B |= (1 << CS12) | (1 << CS10);
//     // Set OCR1A to the equivalent of 2 seconds
//     OCR1A =(0xFFFFL * 2000) / (TIME_TO_FILL_TIMER);
//     // Enable timer1 compare interrupt
//     TIMSK1 |= (1 << OCIE1A);
// }

char converter(char c)
{
  if (c >='a' && c <='z')
    return (c + 'A' - 'a');
  if (c >= 'A' && c <= 'Z')
    return (c  + 'a' - 'A');
  return (c);
  
}

ISR(USART_RX_vect)
{
  char c = converter(uart_rx());
  uart_tx(c);
}

int main() {
  // Initialize the UART
  uart_init();

  sei();
  while (1) {
  }

  return 0;
}