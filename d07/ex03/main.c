#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

int main(int argc, char const *argv[])
{
    ADMUX |= (1 << REFS0) | (1 << REFS1);                                // ref voltage AVCC
    // ADMUX |= (1 << ADLAR);                                // result left adjusted
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // Prescaler
    ADMUX |= (1 << MUX3);

    uint16_t value;


    uart_init();

    while (1)
    {
        ADCSRA |= (1 << ADEN) | (1 << ADSC); // ADC enable + ADC start conversion
        while ((ADCSRA & (1 << ADSC)))

            ; // check if the value of ADSC is one, which means that we can reaad the value
        value = ADC;
        if (value <= 0x010D)
            uart_printstr(" -40 C ou moins\r\n");
        else if (value <= 0x0160)
            uart_printstr(" 25 C ou moins\r\n");
        else if (value <= 0x01E0)
            uart_printnb(25 + ((value - 0x0160) * 100) / (0x01E0 - 0x0160));
        uart_printstr("\r\n");
            // uart_printstr(" 125 C ou moins\r\n");

        


        _delay_ms(20);
    }
    return 0;
}
