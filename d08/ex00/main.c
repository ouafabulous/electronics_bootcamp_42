// #include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#define SS PB2
#define MISO PB4
#define MOSI PB3
#define SCK PB5
#define DDR_SPI DDRB
// #define 
// #define 
// #define 

// uint8_t start_frame = 0b00000000000000000000000000000000;
// uint8_t led_frame = 0b11111111000000000000000011111111;
// uint8_t start_frame = 0b11111111111111111111111111111111;

void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1 << MOSI) | (1 << SCK) | (1 << SS);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}
void SPI_MasterTransmit(char cData)
{
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while (!(SPSR & (1 << SPIF)))
        ;
}


// void SPI_SlaveInit(void)
// {
// /* Set MISO output, all others input */
// DDR_SPI = (1<<DD_MISO);
// /* Enable SPI */
// SPCR = (1<<SPE);
// }
// char SPI_SlaveReceive(void)
// {
// /* Wait for reception complete */
// while(!(SPSR & (1<<SPIF)))
// ;
// /* Return Data Register */
// return SPDR;
// }

int main(int argc, char const *argv[])
{
    // DDRD |= (1 << DDD6);
    SPI_MasterInit();
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);

    SPI_MasterTransmit(0b11100001);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b11111111);
    
    SPI_MasterTransmit(0b11100000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    
    SPI_MasterTransmit(0b11100000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    SPI_MasterTransmit(0b00000000);
    
    SPI_MasterTransmit(0b11111111);
    SPI_MasterTransmit(0b11111111);
    SPI_MasterTransmit(0b11111111);
    SPI_MasterTransmit(0b11111111);
    // SPI_MasterTransmit(BRIGHTNESS_FRAME);
    // SPI_MasterTransmit(BLUE_VALUE);
    // SPI_MasterTransmit(GREEN_VALUE);
    // SPI_MasterTransmit(RED_VALUE);

    while (1)
    {
        // PORTD |= (1 << PORTD6);
    }
    return 0;
}
