#ifndef __UART_H
  #define __UART_H

#include "main.h"

extern UART_HandleTypeDef huart2;

void MX_USART2_UART_Init(void);
void UART2_RxCpltCallback(void);

//структура для USART
typedef struct USART_prop{
	uint8_t usart_buf[20];
	uint8_t usart_cnt;
} USART_prop_ptr;

extern USART_prop_ptr usartprop;
extern char trans_str[64], str[20];

#endif

