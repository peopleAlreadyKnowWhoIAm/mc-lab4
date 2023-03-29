#include "timer.h"

#include <avr/interrupt.h>

static void (*timer_handler)();

ISR(TIMER0_COMPA_vect) { timer_handler(); }

void initTimer0(enum TimerPrescaller prescaller, uint8_t period,
                void (*handler)()) {
  timer_handler = handler;
  // Config timer to CTC mode with OCSR0A
  TCCR0A = _BV(WGM01);
  TCCR0B = _BV(WGM02) | prescaller;

  OCR0A = period;

  TIMSK0 = _BV(OCIE0A);
}