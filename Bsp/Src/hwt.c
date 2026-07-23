#include "hwt.h"
float yaw;
uint8_t rx_byte;

void hwt_Init(void)
{
    uint8_t key_cmd[] = {0xFF, 0xAA, 0x69, 0x88, 0xB5};
    HAL_UART_Transmit(&huart1,key_cmd,sizeof(key_cmd),1000);
    HAL_Delay(10);
    uint8_t set_cmd[]= {0xFF,0xAA,0x76,0x00,0x00};
    HAL_UART_Transmit(&huart1,set_cmd,sizeof(set_cmd),1000);
    HAL_Delay(10);
    uint8_t end[]= {0xFF,0xAA,0x00,0x00,0x00};
    HAL_UART_Transmit(&huart1,end,sizeof(end),1000);
    HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
}
int ParseYaw(uint8_t *buf,float *p)
{
    if (buf[0] != RHEAD1 || buf[1] != RHEAD2)
    {
        return 0;
    }

    int16_t raw= (int16_t)(buf[7] <<8) | buf[6];
    *p = (float) raw * 180.0f / 32768.0f;

    return 1;
}
