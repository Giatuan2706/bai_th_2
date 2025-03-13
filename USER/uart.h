#ifndef UART_H
#define UART_H

#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include <stdio.h>

void UART_Init(void);
void UART_SendChar(char c);
void UART_SendString(char *str);
void UART_SendNumber(uint8_t num);
void UART_Debug_DHT11(uint8_t temperature, uint8_t humidity);

#endif
