#ifndef APPLICATION_H
#define APPLICATION_H

#include "defines.h"

extern int8_t pwr;
//xtern uint8_t ant;
extern uint8_t channel;
extern uint32_t serial;
extern uint8_t __xdata Voltage;
extern uint8_t rotate_speed;
extern uint8_t speed_counter;
extern uint8_t speed;
extern uint8_t BUTT;
extern uint8_t GoodCal;

void Setup();
void Loop();
void TimerCallback();
uint8_t GetVoltageOrTemp(uint8_t);
uint8_t CompVersion();

#endif
