#ifndef DHT11_H
#define DHT11_H

#include "stm32f10x.h"

#define DHT11_PORT GPIOB
#define DHT11_PIN  GPIO_Pin_12

// Khai báo các hàm
void DHT11_Init(void);
void DHT11_StartSignal(void);
uint8_t DHT11_CheckResponse(void);
uint8_t DHT11_ReadByte(void);
uint8_t DHT11_GetData(uint8_t *temperature, uint8_t *humidity);

#endif
