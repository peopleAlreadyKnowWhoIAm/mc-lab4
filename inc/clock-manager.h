#ifndef _CLOKC_MANAGER_H_
#define _CLOKC_MANAGER_H_ 

#include "event-manager.h"
#include "7seg-display.h"
#include "button-manager.h"
#include "buzzer.h"


#include <stdbool.h>

#define SEC_DELAY 1000/EVENT_PERIOD_MS/2

#define STOPWATCH_BUFFER_SIZE 10

void StopwatchManagerInit();

void ButtonClicked(uint8_t button);

#endif
