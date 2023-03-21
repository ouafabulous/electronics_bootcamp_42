#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define LED0 PB0
#define LED1 PB1
#define LED2 PB2
#define LED3 PB4
#define BUTTON0 PD2 // SW1 increase the count
#define BUTTON1 PD4 // SW2 select a counter
#define DEBOUNCE_DELAY_MS 10

uint8_t eeprom_addr[4] = {0, 1, 2, 3};

uint8_t counter[4];

int main(int argc, char const *argv[])
{

    uint8_t pressed[2] = {0,0};
    DDRB |= (1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3);
    // DDRD &= ~(1 << BUTTON);
    PORTD |= (1 << BUTTON0) | (1 << BUTTON1);

    uint8_t i = 0;
    while (i < 4)
    {
        counter[i] = eeprom_read_byte((uint8_t *)&eeprom_addr[i]);
        if (!(counter[i] & 0xFF))
        {
            counter[i] = 0;
            eeprom_update_byte((uint8_t *)&eeprom_addr[i], counter[i]);
        }
        i++;
    }

    i = 0;
    while (1)
    {
        if (!pressed[1] && !(PIND & (1 << BUTTON1)))
        {
            pressed[1] = 1;

            i++;
            i %= 4;
            _delay_ms(DEBOUNCE_DELAY_MS);
        }

        if (PIND & (1 << BUTTON1))
            pressed[1] = 0;

        if (!pressed[0] && !(PIND & (1 << BUTTON0)))
        {
            pressed[0] = 1;

            counter[i]++;
            counter[i] %= 15;

            _delay_ms(DEBOUNCE_DELAY_MS);
            eeprom_update_byte((uint8_t *)&eeprom_addr[i], counter[i]);
        }

        if (PIND & (1 << BUTTON0))
            pressed[0] = 0;

        if (counter[i] & 0b0001)
            PORTB |= (1 << LED0);
        else
            PORTB &= ~(1 << LED0);

        if (counter[i] & 0b0010)
            PORTB |= (1 << LED1);
        else
            PORTB &= ~(1 << LED1);

        if (counter[i] & 0b0100)
            PORTB |= (1 << LED2);
        else
            PORTB &= ~(1 << LED2);

        if (counter[i] & 0b1000)
            PORTB |= (1 << LED3);
        else
            PORTB &= ~(1 << LED3);
    }

    return 0;
}
