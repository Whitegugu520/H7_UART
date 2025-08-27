#ifndef MYUART_H
#define MYUART_H

#include "main.h"
#include "MYGPIO.h"
#include "stm32h7xx_hal_uart.h" 
#include <string.h>

void MY_UART_Init();
void UART2_TX(char *data,size_t size);



#endif
