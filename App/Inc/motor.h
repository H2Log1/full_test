#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#define Speed_base 150

typedef struct
{
    double now_vel;
    double target_vel;
} MOTOR;

void Motor_Init(void);
void Motor_Stop(void);
void Motor_Set_Vel(int16_t motor_vel);
void Get_Motor_Speed(double *now_vel, TIM_HandleTypeDef *htim);
int getTIMx_DetaCnt(TIM_HandleTypeDef *htim);

extern MOTOR motor_speed[2];

#endif // MOTOR_H