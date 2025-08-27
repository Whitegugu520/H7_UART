#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"
#include "tim.h"

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void Motor_Init(void); //启动电机
void Motor_SetSpeed(int speed); //设置电机速度

#endif