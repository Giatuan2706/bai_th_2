#include "dht11.h"
#include "delay.h"
#include "uart.h"  

// Bien to�n cuc de luu du lieu tu DHT11
uint8_t u8Buff[5] = {0};  
uint8_t u8CheckSum;  

// H�m khoi tao GPIO cho DHT11
void DHT11_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Pin = DHT11_PIN;
    gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &gpioInit);
}

// H�m gui t�n hieu khoi dong cho DHT11
void DHT11_StartSignal(void)
{
    GPIO_ResetBits(DHT11_PORT, DHT11_PIN);
    delay_ms(20);  												// K�o xuong muc thap �t nhat 18ms
    GPIO_SetBits(DHT11_PORT, DHT11_PIN);
}

// H�m kiem tra phan hoi tu DHT11
uint8_t DHT11_CheckResponse(void)
{
    uint16_t u16Tim = 0;

    // Chuyen sang input de nhan t�n hieu tu DHT11
    GPIO_InitTypeDef gpioInit;
    gpioInit.GPIO_Pin = DHT11_PIN;
    gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DHT11_PORT, &gpioInit);

    // Kiem tra xem cam bien c� phan hoi kh�ng
    TIM_SetCounter(TIM2, 0);
    while (TIM_GetCounter(TIM2) < 10)
    {
        if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
        {
            break;
        }
    }
    u16Tim = TIM_GetCounter(TIM2);
    if (u16Tim >= 10) return 0;  // Kh�ng c� phan hoi

    return 1; // Cam bien phan hoi th�nh c�ng
}

// H�m doc 1 byte tu DHT11
uint8_t DHT11_ReadByte(void)
{
    uint8_t i, value = 0;
    uint16_t u16Tim;

    for (i = 0; i < 8; i++)
    {
        // Cho ch�n l�n HIGH
        TIM_SetCounter(TIM2, 0);
        while (TIM_GetCounter(TIM2) < 65)
        {
            if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
            {
                break;
            }
        }

        // Kiem tra thoi gian phan hoi
        u16Tim = TIM_GetCounter(TIM2);
        if ((u16Tim >= 65) || (u16Tim <= 45))
        {
            return 0; // Loi nhan du lieu
        }

        // Cho ch�n xuong LOW
        TIM_SetCounter(TIM2, 0);
        while (TIM_GetCounter(TIM2) < 80)
        {
            if (!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_PIN))
            {
                break;
            }
        }

        // Shift du lieu v� doc gi� tri bit
        value <<= 1;
        if (u16Tim > 45)
        {
            value |= 1;  // Nhan duoc bit 1
        }
    }

    return value;
}

// H�m doc du lieu nhiet do v� do am tu DHT11
uint8_t DHT11_GetData(uint8_t *temperature, uint8_t *humidity)
{
    DHT11_StartSignal();

    if (DHT11_CheckResponse())
    {
        u8Buff[0] = DHT11_ReadByte(); // �o am nguy�n
        u8Buff[1] = DHT11_ReadByte(); // �o am thap ph�n (lu�n = 0)
        u8Buff[2] = DHT11_ReadByte(); // Nhiet do nguy�n
        u8Buff[3] = DHT11_ReadByte(); // Nhiet do thap ph�n (lu�n = 0)
        u8Buff[4] = DHT11_ReadByte(); // Checksum

        // Kiem tra checksum
        u8CheckSum = u8Buff[0] + u8Buff[1] + u8Buff[2] + u8Buff[3];
        if (u8CheckSum != u8Buff[4])
        {
            return 0;  // Du lieu kh�ng hop le
        }

        // G�n gi� tri cho bien dau ra
        *humidity = u8Buff[0];
        *temperature = u8Buff[2];

        // Debug du lieu qua UART
        UART_Debug_DHT11(*temperature, *humidity);

        return 1; // �oc du lieu th�nh c�ng
    }

    return 0; // Loi khi doc du lieu
}
