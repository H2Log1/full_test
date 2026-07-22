#include "main.h"
#include "tim.h"
#include "motor.h"

// 使能电机引脚
#define MOTOR1_ENABLE_GPIO GPIOA
#define MOTOR1_ENABLE_PIN GPIO_PIN_12
#define MOTOR2_ENABLE_GPIO GPIOD
#define MOTOR2_ENABLE_PIN GPIO_PIN_3
// 单/双极性引脚
#define MOTOR_BIPOLAR_GPIO GPIOB
#define MOTOR_BIPOLAR_PIN GPIO_PIN_12

MOTOR motor_speed[2] = {
    {0.0, 0.0},
    {0.0, 0.0}};

void Motor_Init(void)
{
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4500);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4500);
    HAL_GPIO_WritePin(MOTOR_BIPOLAR_GPIO, MOTOR_BIPOLAR_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR1_ENABLE_GPIO, MOTOR1_ENABLE_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR2_ENABLE_GPIO, MOTOR2_ENABLE_PIN, GPIO_PIN_SET);
}

void Motor_Stop(void)
{
    HAL_GPIO_WritePin(MOTOR1_ENABLE_GPIO, MOTOR1_ENABLE_PIN, GPIO_PIN_RESET);
}

void Motor_Set_Vel_1(int16_t delta_motor_vel)
{
    if (delta_motor_vel > 4500)
    {
        delta_motor_vel = 4500;
    }
    else if (delta_motor_vel < -4500)
    {
        delta_motor_vel = -4500;
    }
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 4500 + delta_motor_vel);
    // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4500 - delta_motor_vel);
}

void Motor_Set_Vel_2(int16_t delta_motor_vel)
{
    if (delta_motor_vel > 4500)
    {
        delta_motor_vel = 4500;
    }
    else if (delta_motor_vel < -4500)
    {
        delta_motor_vel = -4500;
    }
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4500 - delta_motor_vel);
    // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 4500 - delta_motor_vel);
}


int getTIMx_DetaCnt(TIM_HandleTypeDef *htim)
{
    int cnt;
    cnt = htim->Instance->CNT - 0x7FFF;
    htim->Instance->CNT = 0x7fff;
    return cnt;
}

void Get_Motor_Speed(double *now_vel, TIM_HandleTypeDef *htim)
{
    *now_vel = (double)getTIMx_DetaCnt(htim) / 2.72; // round/100s
}