#include "7seg-display.h"

const uint8_t symbol_codes[] = {
  0x3f, //0
  0x06, //1
  0x5b, //2
  0x4f, //3
  0x66, //4
  0x6d, //5
  0x7d, //6
  0x07, //7
  0x7f, //8
  0x6f, //9
  0b00000010, //a
  0b01100000, //b
  0b00110000, //c
  0b01000010, //d
  0b00110000, //e
  0b00111000, //f
};

static volatile uint8_t buffer_data[DISPLAY_DIGIT_WIDTH];

void _subDisplayWrite();

int8_t DisplayWrite(uint8_t data[]) {
  for(uint8_t i = 0; i < DISPLAY_DIGIT_WIDTH; i++){
    buffer_data[i] = symbol_codes[data[i]];
  }
  return 0;
}

void DisplayEnable() {
  DISPLAY_DIGIT_PORT |= ~(0xff << DISPLAY_DIGIT_WIDTH);
  _subDisplayWrite();
}

void _subDisplayWrite() {
  static uint8_t counter = 0;
  DISPLAY_DIGIT_PORT |= _BV(counter);
  counter++;
  if(counter == DISPLAY_DIGIT_WIDTH) {
    counter = 0;
  }
  DISPLAY_DIGIT_PORT &= ~_BV(counter);
  DISPLAY_DATA_PORT = buffer_data[counter];
  spawnEvent((Event){.delay = DISPLAY_DELAY, .func = _subDisplayWrite});
}