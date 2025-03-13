#include "uart.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void UART_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    // Cau hình chân PA9 (TX)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Cau hình chân PA10 (RX)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Cau hình UART1 (Baudrate: 9600)
    USART_InitStruct.USART_BaudRate = 9600;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStruct);

    // Bat UART1
    USART_Cmd(USART1, ENABLE);
}

// Hàm gui 1 ký tu
void UART_SendChar(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART_SendData(USART1, c);
}

// Hàm gui chuoi
void UART_SendString(char *str)
{
    while (*str)
    {
        UART_SendChar(*str++);
    }
}

// Hàm gui so nguyên (dang ASCII)
void UART_SendNumber(uint8_t num)
{
    char buffer[4];  
    sprintf(buffer, "%d", num);
    UART_SendString(buffer);
}

// Hàm debug du lieu DHT11 qua UART
void UART_Debug_DHT11(uint8_t temperature, uint8_t humidity)
{
    UART_SendString("Temperature: ");
    UART_SendNumber(temperature);
    UART_SendString(" *C\n");

    UART_SendString("Humidity: ");
    UART_SendNumber(humidity);
    UART_SendString(" %\n");
}
