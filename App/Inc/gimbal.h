#ifndef GIMBAL_H
#define GIMBAL_H

#include "gimbal.h"
#include "main.h"
#include "Emm_V5.h"

typedef struct
{
    int16_t addr;
    int16_t dir;
    int16_t vel;
    int16_t round;
    bool state;
    bool snF;
} GIMBAL;

GIMBAL gimbal[2] = {
    {0x01, 0, 0, 0, true, false},
    {0x02, 0, 0, 0, true, false}};

void Gimbal_Init(void);
extern GIMBAL gimbal[2];

#endif // !GIMBAL_H