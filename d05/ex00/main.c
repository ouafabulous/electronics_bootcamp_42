#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#define LED0 PB0
#define LED1 PB1
#define LED2 PB2
#define LED3 PB4
#define BUTTON PD2
#define DEBOUNCE_DELAY_MS 10

#define EEPROM_ADDR 0

#define ADDR_COUNTER 0

uint8_t counter;

int main(int argc, char const *argv[])
{
uint8_t pressed;    
DDRB |= (1 << LED0) | (1 << LED1) | (1 << LED2) | (1 << LED3);
// DDRD &= ~(1 << BUTTON);
PORTD |= (1 << BUTTON);

counter = eeprom_read_byte((uint8_t*)EEPROM_ADDR);

if (!(counter & 0xFF))
{
    counter = 0;
    eeprom_update_byte((uint8_t*)EEPROM_ADDR, counter);
}
while (1)
{

if (!pressed && !(PIND & (1 << BUTTON)))
{
    pressed = 1;

    counter++;
    if (counter > 15)
        counter = 0;

    _delay_ms(DEBOUNCE_DELAY_MS);
    eeprom_update_byte((uint8_t*)EEPROM_ADDR, counter);
}

if (PIND & (1 << BUTTON))
    pressed = 0;

if (counter & 0b0001)
    PORTB |= (1 << LED0);
else
    PORTB &= ~(1 << LED0);

if (counter & 0b0010)
    PORTB |= (1 << LED1);
else
    PORTB &= ~(1 << LED1);

if (counter & 0b0100)
    PORTB |= (1 << LED2);
else
    PORTB &= ~(1 << LED2);

if (counter & 0b1000)
    PORTB |= (1 << LED3);
else
    PORTB &= ~(1 << LED3);
}

return 0;
}





