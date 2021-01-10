
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

const int pause = 250;

void blink_lights(void) {
  /* Turns lights sequentially on arduino ports 2, 7 and 12, chip atmega328p
   *
   */

  DDRD = 0xFF;
  DDRB = 0xFF;

  while (1) {
    PORTD |= 1 << PORTD2;
    _delay_ms(pause);
    PORTD |= 1 << PORTD7;
    _delay_ms(pause);
    PORTB = 1 << PORTB4;
    _delay_ms(pause);
    PORTD = 0x00;
    PORTB = 0x00;

    _delay_ms(pause);
  }
}

int main(void) { blink_lights(); }
