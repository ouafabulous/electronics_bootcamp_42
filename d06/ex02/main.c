#include <avr/io.h>
#include <avr/eeprom.h>
#include <util/delay.h>


#define LED_R PD5 //OC0B
#define LED_G PD6 //OC0A
#define LED_B PD3 //OC2B
void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0B = r;
    OCR0A = g;
    OCR2B = b;
}
void wheel(uint8_t pos)
{
    pos = 255 - pos;
    if (pos < 85)
    {
        set_rgb(255 - pos * 3, 0, pos * 3);
    }
    else if (pos < 170)
    {
        pos = pos - 85;
        set_rgb(0, pos * 3, 255 - pos * 3);
    }
    else
    {
        pos = pos - 170;
        set_rgb(pos * 3, 255 - pos * 3, 0);
    }
}

void init_rgb()
{
    DDRD |= (1 << LED_R) | (1 << LED_G) | (1 << LED_B);

    // TIMER1
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    TCCR0A |= (1 << COM0B1) | (1 << COM0A1);
    TCCR0B |= (1 << CS00);

    // TIMER2

    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2A |= (1 << COM2B1);
    TCCR2B |=  (1 << CS20);

    TCNT0 = 0;
    TCNT2 = 0;

    OCR0A = 0;
    OCR0B = 0;
    OCR2B = 0;

}



int main(int argc, char const *argv[])
{
    init_rgb();
    while (1)
    {

    int i = 0;
    while (i < 256)

    {
        wheel(i);
        i++;
        _delay_ms(10);
    }
    }

   return 0;
}
