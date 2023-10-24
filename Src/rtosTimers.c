#include "rtosTimers.h"

osTimerId osSoftTimer1Handle;
osTimerId osSoftTimer2Handle;

EventGroupHandle_t xEventGroupFirst;

/* osSoftTimer1Callback function */
void osSoftTimer1Callback(void const * argument)
{
  /* USER CODE BEGIN osSoftTimer1Callback */
	uint32_t timer1Period;
	HAL_GPIO_TogglePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin);
	xEventGroupSetBits (xEventGroupFirst, EVENT_TIM1_MASK);
	if (xQueueReceive(led1TimerPeriodQueueHandle, &timer1Period, 0) == pdPASS) 
	{
		xTimerChangePeriod(osSoftTimer1Handle, timer1Period, 0);
	}
  /* USER CODE END osSoftTimer1Callback */
}

/* osSoftTimer2Callback function */
void osSoftTimer2Callback(void const * argument)
{
  /* USER CODE BEGIN osSoftTimer2Callback */
	uint32_t timer2Period;
	xEventGroupSetBits (xEventGroupFirst, EVENT_TIM2_MASK);
	if (xQueueReceive(led2TimerPeriodQueueHandle, &timer2Period, 0) == pdPASS) 
	{
		xTimerChangePeriod(osSoftTimer2Handle, timer2Period, 0);
	}
  /* USER CODE END osSoftTimer2Callback */
}
