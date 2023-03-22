#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

int main(int argc, char const *argv[])
{
    ADMUX |= (1 << REFS0);    //ref voltage AVCC
    ADCSRA |= (1 << ADEN) | (1 << ADSC); //ADC enable + ADC start conversion
    ADMUX |= (1 << ADLAR); // result left adjusted

    uart_init();

    while (1)
    {
    if ( !(ADCSRA & (1 <<ADSC))) //check if the value of ADSC is one, which means that we can reaad the value 
    {
        uint8_t value = ADCH;
        uart_printnb_hex(value);
        uart_printstr("/r/n");
        _delay_ms(20);
    }
    }
    return 0;
}
