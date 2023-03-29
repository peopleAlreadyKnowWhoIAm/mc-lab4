#include "button-manager.h"

static volatile uint8_t state = 0;
static volatile uint8_t clicked = 0;

void _checkClicked() {
  uint8_t data = (~BUTTON_PIN & ~(0xff << 4));
  for (uint8_t mask = 0b1, i = 0; mask != _BV(BUTTON_COUNT);
       (mask <<= 1), i++) {
    if (data & mask) {
      if (state & mask && !(clicked & mask)) {
        clicked |= mask;
        ButtonClicked(i);
      } else {
        state |= mask;
      }
    } else {
      if (state & mask && clicked & mask) {
        state &= ~mask;
      } else {
        clicked &= ~mask;
      }
    }
  }
  spawnEvent((Event){.delay = BUTTON_RECHECK_PERIOD, .func = _checkClicked});
}

void ButtonsInit() {
  spawnEvent((Event){.delay = BUTTON_RECHECK_PERIOD, .func = _checkClicked});
}