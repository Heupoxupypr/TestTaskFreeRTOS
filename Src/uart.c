#include "uart.h"

UART_HandleTypeDef huart2;
char trans_str[64] = {0}, str[20] = {0}; //буферы дл€ данных полученных по UART
USART_prop_ptr usartprop; //Ёкземпл€р структуры USART_prop_ptr

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void UART2_RxCpltCallback(void)
{
	uint8_t b, last_i = 0, j = 0;
  b = str[0];
	uint8_t data[3][20] = {0};
	
	if ((usartprop.usart_cnt>20)||(b == 0x0D) || (b == 0x0A))
	{
		sprintf(trans_str, "\n\r");
		HAL_UART_Transmit(&huart2, (uint8_t*)trans_str, strlen(trans_str), 1000);
		usartprop.usart_buf[usartprop.usart_cnt] = '\0';
		HAL_UART_Transmit(&huart2, (uint8_t*)usartprop.usart_buf, usartprop.usart_cnt, 1000);
		sprintf(trans_str, "\n\r");
		HAL_UART_Transmit(&huart2, (uint8_t*)trans_str, strlen(trans_str), 1000);
		
		if (!strcmp((char*)usartprop.usart_buf, "toogleExecAll")){
				osSemaphoreRelease (myBinaryToogleTaskLed1SemHandle);
				osSemaphoreRelease (myBinaryToogleTaskLed2SemHandle);
				usartprop.usart_cnt=0;
				HAL_UART_Receive_IT(&huart2,(uint8_t*)str,1);
				return;
			}
		else
		{

			for (uint8_t i = last_i; i < usartprop.usart_cnt; i++)
			{
				if (usartprop.usart_buf[i] ==  ':') {
					for (uint8_t y = last_i, k = 0; y < i; y++, k++) {
						data[j][k] = usartprop.usart_buf[y];
					}
					last_i = ++i;
					j++;
					if (j >= 3)
						break;
				}
			}
			if (j < 3) {
				for (uint8_t y = last_i, k = 0; y < usartprop.usart_cnt; y++, k++) {
							data[j][k] = usartprop.usart_buf[y];
				}
			}
			if (!strcmp((char*)data[0], "delayAll")){
				osMessagePut (led1TimerPeriodQueueHandle, atoi((char*)data[1]), portMAX_DELAY);
				osMessagePut (led2TimerPeriodQueueHandle, atoi((char*)data[1]), portMAX_DELAY);
			}
			else if (!strcmp((char*)data[0], "delay")){
				switch (atoi((char*)data[1])) {
					case 1:
						osMessagePut (led1TimerPeriodQueueHandle, atoi((char*)data[2]), portMAX_DELAY);
						break;
					case 2:
						osMessagePut (led2TimerPeriodQueueHandle, atoi((char*)data[2]), portMAX_DELAY);
						break;
					default:
						sprintf(trans_str, "Unknown command\n\r");
						HAL_UART_Transmit(&huart2, (uint8_t*)trans_str, strlen(trans_str), 1000);
						break;
				}
			}
			else if (!strcmp((char*)data[0], "toogleExec")){
				switch (atoi((char*)data[1])) {
					case 1:
						osSemaphoreRelease (myBinaryToogleTaskLed1SemHandle);
						break;
					case 2:
						osSemaphoreRelease (myBinaryToogleTaskLed2SemHandle);
						break;
					default:
						sprintf(trans_str, "Unknown command\n\r");
						HAL_UART_Transmit(&huart2, (uint8_t*)trans_str, strlen(trans_str), 1000);
						break;
				}
			}
			else if (!strcmp((char*)data[0], "pwm")){
				if (atoi((char*)data[1]) <= 100){
					osMessagePut (pwmDataQueueHandle, atoi((char*)data[1]), portMAX_DELAY);
				}
				else {
					osMessagePut (pwmDataQueueHandle, 100, portMAX_DELAY);
				}
				osMessagePut (pwmDataQueueHandle, atoi((char*)data[2]), portMAX_DELAY);
			}
			else {
				sprintf(trans_str, "Unknown command\n\r");
				HAL_UART_Transmit(&huart2, (uint8_t*)trans_str, strlen(trans_str), 1000);
			}
		}
		memset (data, 0, sizeof(data));
		usartprop.usart_cnt=0;
	}
	else
	{
		usartprop.usart_buf[usartprop.usart_cnt] = b;
		usartprop.usart_cnt++;
	}

	HAL_UART_Receive_IT(&huart2,(uint8_t*)str,1);
}
