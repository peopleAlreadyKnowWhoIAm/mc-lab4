#ifndef _7SEG_DISPLAY_H_
#define _7SEG_DISPLAY_H_

#include <avr/io.h>

#include "event-manager.h"

#define DISPLAY_DELAY 1

#define DISPLAY_DATA_PORT PORTD
//Takes first 
#define DISPLAY_DIGIT_PORT PORTC
#define DISPLAY_DIGIT_WIDTH 6

void DisplayEnable();

int8_t DisplayWrite(uint8_t data[]); 



#endif