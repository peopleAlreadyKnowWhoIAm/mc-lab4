#ifndef _BUZZER_H_
#define _BUZZER_H_

#include <avr/io.h>
#include <stdbool.h>

#define BUZZER_PORT PORTB
#define BUZZER_POS PB4

#include "event-manager.h"

int8_t BuzzerDoubleSignal();

int8_t BuzzerLongSignal();

int8_t BuzzerShortSignal();

#endif