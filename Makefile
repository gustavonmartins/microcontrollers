
doit:
	avr-gcc -Wall -Wextra -Werror -g -Os -mmcu=atmega328p -c main.c
	avr-gcc -g -mmcu=atmega328p main.o -o main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:main.hex:i
