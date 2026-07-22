#ifndef INIT_H
#define INIT_H

#include "tim.h"
#include "multi_button.h"
#include "pid.h"

void Tim_Init(void);

extern Pid_t motor_pid[2];

#endif // !INIT_H