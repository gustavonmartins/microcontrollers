
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

double dutyCycle = 0.01;
void interrupt_timer_8bits() {
  /*
   * This generates PWM signal. Its will be on PORTD6, which is linked to OCR0A.
   * It seems that 0A imposes specific Timer Control Register
   */

  // Will blink on Port B1
  DDRD = 1 << PORTD6;

  // Sets Timer/Counter Control Register at to generate fast PWM
  TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);

  // Prepares to create an interrupt if time matches
  TIMSK0 = 1 << TOIE0;
  // Turns off power after reaching 50 pct
  sei();
  // Sets pre-scaler to /1
  TCCR0B = (1 << CS00);

  // When 10ms is reached, an interrupt is produced
  //
  while (1) {
    _delay_ms(100);
    dutyCycle += 0.05;
    OCR0A = dutyCycle * 255;
    if (dutyCycle >= 1) {
      dutyCycle = 0;
    }
  }
}

ISR(TIMER0_OVF_vect) {}

int main() { interrupt_timer_8bits(); }
