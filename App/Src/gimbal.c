#include "gimbal.h"
#include "main.h"
#include "Emm_V5.h"

void Gimbal_Init(void)
{
    Emm_V5_En_Control(gimbal[0].addr, gimbal[0].state, gimbal[0].snF);
    HAL_Delay(10);
    Emm_V5_En_Control(gimbal[1].addr, gimbal[1].state, gimbal[1].snF);
    HAL_Delay(10);
}