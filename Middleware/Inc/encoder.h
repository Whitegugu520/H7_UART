#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern int Encoder1_value = 0;
extern int Encoder1_value_last = 0;
extern int Encoder1_position = 0;


void Encoder_Init(void); 
int Encoder1_Position(void);
int Encoder1_Speed(void);
void Encoder_Update(TIM_HandleTypeDef *tim);



#endif
