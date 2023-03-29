#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include "timer.h"

#include <avr/io.h>

#define EVENT_BUFFER 128

// T = (2*EVENT_PRESCALLER*(EVENT_CYCLE_PERIOD+1)/f_clck[F_CPU]
#define EVENT_PRESCALLER TimerPrescaller_256
#define EVENT_CYCLE_PERIOD 124

#define EVENT_PERIOD_MS 2


typedef struct Event {
  // Each number - 2ms
  uint8_t delay;
  void(*func)();
} Event;

void EventManagerInit();

int8_t spawnEvent(Event event);

void handleTimer();

#endif