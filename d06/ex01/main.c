#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>


#define LED_B PD3
#define LED_R PD5
#define LED_G PD6

int main(int argc, char const *argv[])
{
DDRD |= (1 << LED_R) | (1 << LED_G) | ( 1 << LED_B);
    while (1)
    {
        PORTD = (1 << LED_R);
        _delay_ms(1000);
        PORTD = (1 << LED_G);
        _delay_ms(1000);
        PORTD = (1 << LED_B);
        _delay_ms(1000);
        PORTD = (1 << LED_R) | (1 << LED_G);
        _delay_ms(1000);
        PORTD = (1 << LED_G) | (1 << LED_B);
        _delay_ms(1000);
        PORTD = (1 << LED_R) | (1 << LED_B);
        _delay_ms(1000);
        PORTD = (1 << LED_R) | (1 << LED_G) | (1 << LED_B);
        _delay_ms(1000);
    }
    return 0;
}
