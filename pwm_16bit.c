
#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void start_pwm(double dutyCycle) {
  /*
   * This generates PWM signal. Its will be on PORTD6, which is linked to OCR0A.
   * It seems that 0A imposes specific Timer Control Register
   */

  // Will blink on Port B1, OC1A
  DDRB = 1 << PORTB1;

  // Sets Timer/Counter Control Register at to generate fast PWM
  TCCR1A = (1 << COM1A1) | (1 << WGM11);

  // 312.5 ticks are needed for 50Hz from 160 Mhz with /1024 prescaler, so 9
  // bits can represent 312 ticks
  ICR1 = 312;

  // Prepares to create an interrupt if time matches
  TIMSK1 = 1 << TOIE1;
  // Turns off power after reaching 50 pct
  sei();

  OCR1A = (int)(dutyCycle * 312);
  // Sets pre-scaler to /1024
  TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM13) | (1 << WGM12);

  /// Period is 16.32ms with 16/1024 Mhz, 8bit counter
  //
}

ISR(TIMER1_OVF_vect) {}

int main() {

  double dutyCycle = 544.0 / 20000.0;
  start_pwm(dutyCycle);

  while (1) {
  }
}
