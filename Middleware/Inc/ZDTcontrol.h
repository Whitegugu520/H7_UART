#ifndef ZDTCONTROL_H
#define ZDTCONTROL_H

#include "main.h"
#include "MYUART.h"
#include <string.h>


#define CONTROL_UART huart2

void ZDT_Control_TX();                                                        //不用管
void ZDT_Control_able(uint8_t add,uint8_t a);                                             //用来使能电机  1 enable 0 disable
void ZDT_Control_speed(uint8_t add,uint8_t dir,uint16_t speed,uint8_t acc);          //速度模式控制 地址 + 0xF6 + 方向 + 速度 + 加速度 + 多机同步标志 + 校验字节
void ZDT_Control_position
(uint8_t add,uint8_t dir, uint16_t speed, uint8_t acc, uint32_t pulse, uint8_t mode);
void ZDT_Control_stop(uint8_t add);                                                     //速度模式控制 地址 + 0xF6 + 方向 + 速度 + 加速度 + 多机同步标志 + 校验字节
void ZDT_Control_move(uint8_t add);
uint32_t ZDT_Pulse(float number);            //将圈数换成脉冲数


#endif
