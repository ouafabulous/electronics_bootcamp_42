CC = avr-gcc
FCPU = 16000000UL
NAME = main
MCU = atmega328p
SRC = main.c
DEVICE = /dev/ttyUSB0
PROGRAMMER = arduino

all: hex flash

hex: $(SRC)
	$(CC) -mmcu=$(MCU) -O1 -DF_CPU=$(FCPU) -o $(NAME).bin $(SRC)
	avr-objcopy -O ihex $(NAME).bin $(NAME).hex

flash: $(NAME).hex
	avrdude -p $(MCU) -c $(PROGRAMMER) -P $(DEVICE) -U flash:w:$(NAME).hex

clean: 
	rm -f $(NAME).bin $(NAME).hex