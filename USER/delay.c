#include "delay.h"
#include "stm32f10x_tim.h"

// Hàm khti tao Timer2
void Timer2_Init(void)
{
	// Enable clock for TIM2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	// Init timer
	TIM_TimeBaseInitTypeDef timerInit;
	// mode up counter
	timerInit.TIM_CounterMode = TIM_CounterMode_Up;
	// period = 0xFFFF
	timerInit.TIM_Period = 1000 - 1;
	// prescaler = 72 -1 
	timerInit.TIM_Prescaler = 72 -1;
	// clock divison 
	TIM_TimeBaseInit(TIM2, &timerInit);
	// enable TIM2
	TIM_Cmd(TIM2, ENABLE);
}

// Hàm delay 1ms su dung Timer2
void delay_1ms(void)
{
    TIM_SetCounter(TIM2, 0);  							// Reset bo dem ve 0
    while (TIM_GetCounter(TIM2) < 1000); 		// Cho du 1000 xung = 1ms
}

// Hàm delay nhieu ms
void delay_ms(uint16_t ms)
{
    uint16_t i; // Khai báo bien truoc vòng lap
    for (i = 0; i < ms; i++)
    {
        delay_1ms();
    }
}
