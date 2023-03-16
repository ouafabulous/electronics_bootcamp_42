#include <avr/io.h>

int main()
{
    DDRB |= (1 << PB0);
    PORTB |= (1 << PB0);
    // PORTB &= ~(1 << PB0); //in case we want to turn the LED off!
    while(1) {

    }
    return 0;
}
