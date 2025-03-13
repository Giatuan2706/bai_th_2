#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"  

// Khai báo các hàm delay
void Timer2_Init(void);  		// Khoi tao Timer2
void delay_1ms(void);    		// Delay 1ms
void delay_ms(uint16_t ms); // Delay nhieu ms

#endif
