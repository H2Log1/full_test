#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

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

extern MOTOR motor[2];
extern Pid_t motor_pid;

#endif // MOTOR_H