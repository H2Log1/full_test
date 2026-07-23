#ifndef INIT_H
#define INIT_H

#include "tim.h"
#include "multi_button.h"
#include "pid.h"
#include "filter.h"

void Tim_Init(void);

extern Pid_t motor_pid[2];
extern Pid_t gray_pid;
extern MoveAverageFilter speed_filter[2];

#endif // !INIT_H