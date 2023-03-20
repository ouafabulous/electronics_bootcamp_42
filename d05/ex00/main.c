#include <avr/io.h>
#include <avr/eeprom.h>

#define LED0 PB0
#define LED1 PB1
#define LED2 PB2
#define LED3 PB4
#define BUTTON PD2

#define EEPROM_ADDR 0

#define ADDR_COUNTER 0

uint8_t counter;

int main(int argc, char const *argv[])
{
    
DDRB |= (1 << LED0) | (1 << LED1) | (1 << LED2);
DDRD &= ~(1 << BUTTON);
// PORTD |= (1 << BUTTON);

return 0;
}





