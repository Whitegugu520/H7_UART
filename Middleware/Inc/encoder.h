#ifndef ENCODER_H
#define ENCODER_H

#include "main.h"


extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern int Encoder1_value; 

void Encoder_Init(void); 
void Encoder_Update(void);



#endif
