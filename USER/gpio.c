#include "gpio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void GPIO_Config(void)
{
    // Khai b�o bien cau h�nh GPIO
    GPIO_InitTypeDef gpioInit;

    // Bat clock cho GPIOB v� GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    // Cau h�nh LED debug tr�n PC13 (Output Push-Pull)
    gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioInit.GPIO_Pin = GPIO_Pin_13;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpioInit);

    // Cau h�nh DHT11 tr�n PB12 (Output Open-Drain)
    gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
    gpioInit.GPIO_Pin = GPIO_Pin_12;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpioInit);
}
