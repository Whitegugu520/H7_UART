#include "encoder.h"

#define ENCODER1_TIM htim3
#define ENCODER1_TIM_CHANNEL TIM_CHANNEL_ALL
#define ENCODER1_RES 13
#define ENCODER1_TIMDELAY 20  //每次update时间，单位ms

int Encoder1_value = 0;
int Encoder1_value_last = 0;
int Encoder1_position = 0;
void Encoder_Init(void) 
{
    HAL_TIM_Encoder_Start(&ENCODER1_TIM, ENCODER1_TIM_CHANNEL);
    __HAL_TIM_SET_COUNTER(&ENCODER1_TIM, 30000);
}
void Encoder_Update(TIM_HandleTypeDef *tim) //更新编码器数值
{
    Encoder1_value_last = Encoder1_value;
    Encoder1_value = __HAL_TIM_GET_COUNTER(tim) - 30000;
    Encoder1_position += Encoder1_value;
    __HAL_TIM_SET_COUNTER(tim, 30000);
}
int Encoder_Position(TIM_HandleTypeDef *tim) //获取位置，用增量式
{
    Encoder1_Update(tim);
    return Encoder1_position;
}
int Encoder1_Speed()    //TODU 还未写完
{
    int speed;
    speed = (Encoder1_value - Encoder1_value_last) / ENCODER1_TIMDELAY;
    return speed;
}