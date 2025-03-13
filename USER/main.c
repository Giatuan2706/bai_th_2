#include "stm32f10x.h"
#include "gpio.h"
#include "delay.h"
#include "dht11.h"
#include "uart.h"

int main()
{
    uint8_t temperature = 0, humidity = 0;

    GPIO_Config();
    Timer2_Init();
    DHT11_Init();
    UART_Init();  

    while (1)
    {
        DHT11_GetData(&temperature, &humidity);  // Du lieu duoc gui qua UART
        delay_ms(1000);
    }
}
