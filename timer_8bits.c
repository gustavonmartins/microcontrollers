
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>

int timeLoops = 0;
void interrupt_timer_8bits() {
  /*
   * Plays with interrupts thru timers. This uses CTC mode as waveform
   * generation mode for TCCR0A
   *
   * Pre-scaler is set on register TCCR0B
   *
   * Clock is too quick, even with pre-scaler, so needs to loop many times.
   * Every loop will be set to 10ms, which is 195 ticks
   *
   * Will blink light on led, which is digital pin 13 (Port B5)
   */

  // Will blink on led, Port B5
  DDRB = 1 << PORTB5;

  // Sets Timer/Counter Control Register at to generate CTC waveform, clearing
  // the counter after a match
  TCCR0A = 1 << WGM01;

  // Sets pre-scaler to /1024
  TCCR0B = (1 << CS02) | (1 << CS00);

  // Reaches 10 ms every 156 ticks via Output Compare Register A
  OCR0A = 156;

  // Prepares to create an interrupt if time matches
  TIMSK0 = 1 << OCIE0A;
  sei();
  // When 10ms is reached, an interrupt is produced
  //
  while (1) {
  }
}

ISR(TIMER0_COMPA_vect) {
  timeLoops++; // Each loop is 10ms per design
  if (timeLoops >= 100) {
    timeLoops = 0;
    PORTB ^= (1 << PORTB5);
  }
}

int main() { interrupt_timer_8bits(); }
