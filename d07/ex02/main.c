#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

int main(int argc, char const *argv[])
{
    ADMUX |= (1 << REFS0);                                // ref voltage AVCC
    // ADMUX |= (1 << ADLAR);                                // result left adjusted
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Prescaler

    uint16_t value;


    uart_init();

    while (1)
    {
        ADMUX &= 0b11110000;
        ADCSRA |= (1 << ADEN) | (1 << ADSC); // ADC enable + ADC start conversion
        while ((ADCSRA & (1 << ADSC)))

            ; // check if the value of ADSC is one, which means that we can reaad the value
        value = ADC;
        uart_printnb_hex(value);
        uart_printstr(", ");
        
        ADMUX &= 0b11110000;
        ADMUX |= (1 << MUX0);
        ADCSRA |= (1 << ADEN) | (1 << ADSC); // ADC enable + ADC start conversion
        while ((ADCSRA & (1 << ADSC)))

            ; // check if the value of ADSC is one, which means that we can reaad the value
        value = ADC;
        uart_printnb_hex(value);
        uart_printstr(", ");
        
        ADMUX &= 0b11110000;
        ADMUX |= (1 << MUX1);
        ADCSRA |= (1 << ADEN) | (1 << ADSC); // ADC enable + ADC start conversion
        while ((ADCSRA & (1 << ADSC)))

            ; // check if the value of ADSC is one, which means that we can reaad the value
        value = ADC;
        uart_printnb_hex(value);
        uart_printstr("\r\n");

        _delay_ms(20);
    }
    return 0;
}
