#ifndef __RTOS_TIMERS
  #define __RTOS_TIMERS

#include "main.h"

extern osTimerId osSoftTimer1Handle;
extern osTimerId osSoftTimer2Handle;

extern EventGroupHandle_t xEventGroupFirst;

void osSoftTimer1Callback(void const * argument);
void osSoftTimer2Callback(void const * argument);

#endif
