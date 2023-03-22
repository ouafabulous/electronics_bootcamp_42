#ifndef UART_H
# define UART_H

#include "avr/io.h"

#define UART_BAUDRATE 115200
#define MYUBRR 8 // Technically, F_CPU / (16L * UART_BAUDRATE) - 1 -> 7.68 =~ 8
#define BASE_16 "0123456789ABCDEF"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define RESET_COLOR "\033[0m"

#define RED_ON() uart_printstr(RED_COLOR)
#define GREEN_ON() uart_printstr(GREEN_COLOR)
#define YELLOW_ON() uart_printstr(YELLOW_COLOR)
#define COLOR_OFF() uart_printstr(RESET_COLOR)

void uart_init(void);
void uart_tx(char c);
void uart_printstr(const char *str);
char uart_rx(void);
void uart_printnb(unsigned int nb);
void uart_printnb_hex(unsigned int nb);
void uart_printnb_bin(unsigned int nb);

#endif