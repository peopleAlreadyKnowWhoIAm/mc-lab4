#include "clock-manager.h"

static volatile uint32_t time;

static volatile uint32_t time_memory[STOPWATCH_BUFFER_SIZE];
static volatile uint8_t time_memory_pos = 0;
static volatile uint8_t last_minute_digit = 0;
static volatile struct {
  uint8_t running : 1;
  uint8_t memory_mode : 1;
} state;
void _convertTimeToDigits(uint8_t* digits, uint32_t time);

void _writeTime(uint32_t time) {
  uint8_t nums[6];
  _convertTimeToDigits(nums, time);
  if(nums[3] != last_minute_digit) {
    last_minute_digit = nums[3];
    BuzzerLongSignal();
  }
  DisplayWrite(nums);
}

void _subCounter() {
  time++;
  _writeTime(time/2);
  if (state.running) {
    spawnEvent((Event){.delay = SEC_DELAY, .func = _subCounter});
  }
}

void StopwatchManagerInit() {
  DisplayEnable();
  EventManagerInit();
  ButtonsInit();
  _writeTime(time);
}

void _convertTimeToDigits(uint8_t* digits, uint32_t time) {
  uint8_t hms[] = {time / 3600, (time / 60) % 60, time % 60};
  for (uint8_t i = 0; i < 6; i++) {
    if (i % 2 == 0) {
      digits[i] = hms[i / 2] / 10;
    } else {
      digits[i] = hms[i / 2] % 10;
    }
  }
}

void ButtonClicked(uint8_t button) {
  BuzzerShortSignal();
  if (button == 0) {
    if (state.running) {
      state.running = false;
    } else if (time == 0) {
      state.running = true;
      _subCounter();
    } else {
      time = 0;
      last_minute_digit = 0;
      _writeTime(time);
    }
  } else if (button == 1 && state.running &&
             time_memory_pos < STOPWATCH_BUFFER_SIZE) {
    time_memory[time_memory_pos] = time/2;
    time_memory_pos++;
  } else if (button == 2) {
    time_memory_pos = 0;
    _writeTime(time/2);
  } else if (button == 3 && !state.running && time_memory_pos != 0){
    static int8_t time_memory_show = 0;
    _writeTime(time_memory[time_memory_show]);
    time_memory_show++;
    if(time_memory_show>= time_memory_pos){
      time_memory_show = 0;
    }
  }
}