/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//uint8_t LedStatus = 1;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	usartprop.usart_buf[0]=0;
	usartprop.usart_cnt=0;
	xEventGroupFirst = xEventGroupCreate(); //Создание группы событий
	HAL_UART_Receive_IT(&huart2,(uint8_t*)str,1); //Включение пррерываний по приему UART2
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of myBinaryUartRxSem */
  osSemaphoreDef(myBinaryUartRxSem);
  myBinaryUartRxSemHandle = osSemaphoreCreate(osSemaphore(myBinaryUartRxSem), 1);

  /* definition and creation of myBinaryToogleTaskLed1Sem */
  osSemaphoreDef(myBinaryToogleTaskLed1Sem);
  myBinaryToogleTaskLed1SemHandle = osSemaphoreCreate(osSemaphore(myBinaryToogleTaskLed1Sem), 1);

  /* definition and creation of myBinaryToogleTaskLed2Sem */
  osSemaphoreDef(myBinaryToogleTaskLed2Sem);
  myBinaryToogleTaskLed2SemHandle = osSemaphoreCreate(osSemaphore(myBinaryToogleTaskLed2Sem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	osSemaphoreWait (myBinaryUartRxSemHandle, portMAX_DELAY);
	osSemaphoreWait (myBinaryToogleTaskLed1SemHandle, portMAX_DELAY);
	osSemaphoreWait (myBinaryToogleTaskLed2SemHandle, portMAX_DELAY);
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of osSoftTimer1 */
  osTimerDef(osSoftTimer1, osSoftTimer1Callback);
  osSoftTimer1Handle = osTimerCreate(osTimer(osSoftTimer1), osTimerPeriodic, NULL);

  /* definition and creation of osSoftTimer2 */
  osTimerDef(osSoftTimer2, osSoftTimer2Callback);
  osSoftTimer2Handle = osTimerCreate(osTimer(osSoftTimer2), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of led1StatusQueue */
  osMessageQDef(led1StatusQueue, 2, uint8_t);
  led1StatusQueueHandle = osMessageCreate(osMessageQ(led1StatusQueue), NULL);

  /* definition and creation of led2StatusQueue */
  osMessageQDef(led2StatusQueue, 2, uint8_t);
  led2StatusQueueHandle = osMessageCreate(osMessageQ(led2StatusQueue), NULL);

  /* definition and creation of led1TimerPeriodQueue */
  osMessageQDef(led1TimerPeriodQueue, 2, uint32_t);
  led1TimerPeriodQueueHandle = osMessageCreate(osMessageQ(led1TimerPeriodQueue), NULL);

  /* definition and creation of led2TimerPeriodQueue */
  osMessageQDef(led2TimerPeriodQueue, 2, uint32_t);
  led2TimerPeriodQueueHandle = osMessageCreate(osMessageQ(led2TimerPeriodQueue), NULL);

  /* definition and creation of pwmDataQueue */
  osMessageQDef(pwmDataQueue, 4, uint16_t);
  pwmDataQueueHandle = osMessageCreate(osMessageQ(pwmDataQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of DefaultTask */
  osThreadDef(DefaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  DefaultTaskHandle = osThreadCreate(osThread(DefaultTask), NULL);

  /* definition and creation of BlueLedTask */
  osThreadDef(BlueLedTask, StartBlueLedTask, osPriorityNormal, 0, 128);
  BlueLedTaskHandle = osThreadCreate(osThread(BlueLedTask), NULL);

  /* definition and creation of RedLedTask */
  osThreadDef(RedLedTask, StartRedLedTask, osPriorityNormal, 0, 128);
  RedLedTaskHandle = osThreadCreate(osThread(RedLedTask), NULL);

  /* definition and creation of PWMTask */
  osThreadDef(PWMTask, StartPWMTask, osPriorityIdle, 0, 128);
  PWMTaskHandle = osThreadCreate(osThread(PWMTask), NULL);

  /* definition and creation of UartTask */
  osThreadDef(UartTask, StartUartTask, osPriorityHigh, 0, 128);
  UartTaskHandle = osThreadCreate(osThread(UartTask), NULL);

  /* definition and creation of ToogleLed1Task */
  osThreadDef(ToogleLed1Task, StartToogleLed1Task, osPriorityIdle, 0, 128);
  ToogleLed1TaskHandle = osThreadCreate(osThread(ToogleLed1Task), NULL);

  /* definition and creation of ToogleLed2Task */
  osThreadDef(ToogleLed2Task, StartToogleLed2Task, osPriorityIdle, 0, 128);
  ToogleLed2TaskHandle = osThreadCreate(osThread(ToogleLed2Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */

//Функция обработчик прерываний по USART2
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart2)
	{
		osSemaphoreRelease (myBinaryUartRxSemHandle);			//Выставляем Семафор при получении байта по uart
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
