#ifndef __RTOSTASKS_H
  #define __RTOSTASKS_H

#include "main.h"

extern osThreadId DefaultTaskHandle;
extern osThreadId BlueLedTaskHandle;
extern osThreadId RedLedTaskHandle;
extern osThreadId PWMTaskHandle;
extern osThreadId UartTaskHandle;
extern osThreadId ToogleLed1TaskHandle;
extern osThreadId ToogleLed2TaskHandle;

void StartDefaultTask(void const * argument);
void StartBlueLedTask(void const * argument);
void StartRedLedTask(void const * argument);
void StartPWMTask(void const * argument);
void StartUartTask(void const * argument);
void StartToogleLed1Task(void const * argument);
void StartToogleLed2Task(void const * argument);

#endif
