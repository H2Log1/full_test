#include "main.h"
#include "tim.h"
#include "init.h"
#include "pid.h"

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
}

void PID_Init(void)
{
    Pid_t motor_pid;

    PidInit(&motor_pid, POSITION_PID, 4500, 3000, 2.0f, 1.0f, 1.0f, 1.0f);
}
