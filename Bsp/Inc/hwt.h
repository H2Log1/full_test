#ifndef __HWT_H
#define __HWT_H

#include "main.h"
#include "usart.h"
#define FRAME_SIZE 11 //读格式帧
#define RHEAD1  0x55 //读格式协议头
#define RHEAD2 0x53//z角度的寄存器
#define WHEAD 0xFF,0xAA //写格式协议头
#define hwt_setAngle_addr 0x76 //设置z角度的寄存器（用来设置零漂）
#define hwt_key 0x69 //设置前都需要先解锁寄存器

void hwt_Init(void);
int ParseYaw(uint8_t *buf,float *p);
// int ParseYaw(uint8_t *buf,float *yaw);
extern float yaw;
extern uint8_t rx_byte;
#endif
