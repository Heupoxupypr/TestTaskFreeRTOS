#include "rtosTasks.h"

osThreadId DefaultTaskHandle;
osThreadId BlueLedTaskHandle;
osThreadId RedLedTaskHandle;
osThreadId PWMTaskHandle;
osThreadId UartTaskHandle;
osThreadId ToogleLed1TaskHandle;
osThreadId ToogleLed2TaskHandle;

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the DefaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
//	uint8_t led1TaskStatus = 1, led2TaskStatus = 1;
  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartBlueLedTask */
/**
* @brief Function implementing the BlueLedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartBlueLedTask */
void StartBlueLedTask(void const * argument)
{
  /* USER CODE BEGIN StartBlueLedTask */
	EventBits_t event;
	uint8_t blueLedStatus = 1;
	uint32_t timer1Period = 2000;
	osTimerStart (osSoftTimer1Handle, timer1Period);
  /* Infinite loop */
  for(;;)
  {
		xQueueReceive(led1StatusQueueHandle, &blueLedStatus, 10);
		if (blueLedStatus){
			event = xEventGroupWaitBits (xEventGroupFirst, EVENT_TIM1_MASK, pdTRUE, pdFALSE, 100);
			if (event)
			{
				HAL_GPIO_TogglePin (BLUE_LED_GPIO_Port, BLUE_LED_Pin);
			}
		}
    osDelay(10);
  }
  /* USER CODE END StartBlueLedTask */
}

/* USER CODE BEGIN Header_StartRedLedTask */
/**
* @brief Function implementing the RedLedTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartRedLedTask */
void StartRedLedTask(void const * argument)
{
  /* USER CODE BEGIN StartRedLedTask */
	EventBits_t event;
	uint8_t redLedStatus = 1;
	uint32_t timer2Period = 250;
	osTimerStart (osSoftTimer2Handle, timer2Period);
  /* Infinite loop */
  for(;;)
  {
		xQueueReceive(led2StatusQueueHandle, &redLedStatus, 0);
		if (redLedStatus){
		event = xEventGroupWaitBits (xEventGroupFirst, EVENT_TIM2_MASK, pdTRUE, pdFALSE, 0);
			if (event)
			{
				if(!HAL_GPIO_ReadPin(BLUE_LED_GPIO_Port, BLUE_LED_Pin))
				{
					HAL_GPIO_TogglePin (RED_LED_GPIO_Port, RED_LED_Pin);
				}
				else
				{
					HAL_GPIO_WritePin (RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);
				}
			}
		}
    osDelay(10);
  }
  /* USER CODE END StartRedLedTask */
}

/* USER CODE BEGIN Header_StartPWMTask */
/**
* @brief Function implementing the PWMTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPWMTask */
void StartPWMTask(void const * argument)
{
  /* USER CODE BEGIN StartPWMTask */
	uint16_t pwm_value = 0, ledBright = 100, ledPeriod = 1000;
	int16_t step = 0;
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);

  /* Infinite loop */
  for(;;)
  {
		if (xQueueReceive(pwmDataQueueHandle, &ledBright, 0) == pdPASS){
			xQueueReceive(pwmDataQueueHandle, &ledPeriod, portMAX_DELAY);
		}
	
		if(pwm_value <= 0) 
			step = ((25000*ledBright)/100)/ledPeriod;
		if(pwm_value >= (25000*ledBright)/100) 
			step = -((25000*ledBright)/100)/ledPeriod;
		pwm_value += step;
		TIM1->CCR1 = pwm_value;
		HAL_Delay(1);
  }
  /* USER CODE END StartPWMTask */
}

/* USER CODE BEGIN Header_StartUartTask */
/**
* @brief Function implementing the UartTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUartTask */
void StartUartTask(void const * argument)
{
  /* USER CODE BEGIN StartUartTask */
  /* Infinite loop */
  for(;;)
  {
		osSemaphoreWait (myBinaryUartRxSemHandle, portMAX_DELAY);//Ожидаем установку семафора myBinaryUartRxSemHandle
		UART2_RxCpltCallback();
    osDelay(10);
  }
  /* USER CODE END StartUartTask */
}

/* USER CODE BEGIN Header_StartToogleLed1Task */
/**
* @brief Function implementing the ToogleLed1Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartToogleLed1Task */
void StartToogleLed1Task(void const * argument)
{
  /* USER CODE BEGIN StartToogleLed1Task */
	uint8_t led1TaskStatus = 1;
  /* Infinite loop */
  for(;;)
  {
		osSemaphoreWait(myBinaryToogleTaskLed1SemHandle, portMAX_DELAY);
		led1TaskStatus = !led1TaskStatus;
		osMessagePut (led1StatusQueueHandle, led1TaskStatus, portMAX_DELAY);

    osDelay(10);
  }
  /* USER CODE END StartToogleLed1Task */
}

/* USER CODE BEGIN Header_StartToogleLed2Task */
/**
* @brief Function implementing the ToogleLed2Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartToogleLed2Task */
void StartToogleLed2Task(void const * argument)
{
  /* USER CODE BEGIN StartToogleLed2Task */
	uint8_t led2TaskStatus = 1;
  /* Infinite loop */
  for(;;)
  {
		osSemaphoreWait(myBinaryToogleTaskLed2SemHandle, portMAX_DELAY);
		led2TaskStatus = !led2TaskStatus;
		osMessagePut (led2StatusQueueHandle, led2TaskStatus, portMAX_DELAY);
    osDelay(10);
  }
  /* USER CODE END StartToogleLed2Task */
}
