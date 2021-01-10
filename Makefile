
doit:
	avr-gcc -Wall -Wextra -Werror -g -Os -mmcu=atmega328p -c $(inpfile).c
	avr-gcc -g -mmcu=atmega328p $(inpfile).o -o $(inpfile).elf
	avr-objcopy -j .text -j .data -O ihex $(inpfile).elf $(inpfile).hex
	avr-size -C --mcu=atmega328p $(inpfile).elf
	avrdude -v -p atmega328p -c arduino -P /dev/ttyACM0 -b 115200 -D -U flash:w:$(inpfile).hex:i

view:
	avr-objdump -h -S $(inpfile).elf > $(inpfile).lst	
