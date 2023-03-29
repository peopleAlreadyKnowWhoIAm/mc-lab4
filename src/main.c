#include "main.h"

int main() {
  setup();
  while(1){

  }
  return 0;
}

void setup(){
  DDRC = 0b00111111;
  DDRD = 0xff;
  DDRB = 0b10000;
  PORTB = 0b1111;
  StopwatchManagerInit();
  sei();
}