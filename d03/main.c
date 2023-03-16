#include <avr/io.h>
#include <util/delay.h>

#define UART_BAUDRATE 115200

void uart_init() {
  // Configure baud rate
//   uint16_t ubrr = F_CPU / 16 / UART_BAUDRATE;
  uint16 ubrr = 8;
  UBRR0H = (ubrr >> 8);
  UBRR0L = ubrr;
  
  // Enable UART transmitter
  UCSR0B |= (1 << TXEN0);
  
  // Set frame format: 8 data bits, no parity, 1 stop bit
  UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_tx(char data) {
  // Wait for the UART transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)));
  
  // Transmit the data
  UDR0 = data;
}

int main() {
  // Initialize the UART
  uart_init();

  while (1) {
    // Send 'Z' to the serial port
    uart_tx('Z');

    // Delay for 1 second
    _delay_ms(1000);
  }

  return 0;
}