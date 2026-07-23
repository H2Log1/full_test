#include "main.h"
#include "tim.h"
#include "init.h"
#include "pid.h"
#include "filter.h"

void Tim_Init(void)
{
    //* PWM
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    //* Encoder
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

    HAL_TIM_Base_Start_IT(&htim2);
    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_Base_Start_IT(&htim6); // 中断 1ms
    HAL_TIM_Base_Start_IT(&htim9);
}

Pid_t motor_pid[2]; /*1,2电机速度环pid参数源头*/
Pid_t gray_pid;

MoveAverageFilter speed_filter[2];