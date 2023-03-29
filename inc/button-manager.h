#ifndef _BUTTON_MANAGER_H
#define _BUTTON_MANAGER_H

#include <avr/io.h>

#include "event-manager.h"

#define BUTTON_RECHECK_PERIOD 10

#define BUTTON_PIN PINB

#define BUTTON_COUNT 4

// MUST be implemnted elsewhere
void ButtonClicked(uint8_t button);

void ButtonsInit();

#endif
