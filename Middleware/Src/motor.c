#include "motor.h"

#define MOTOR1_PWM htim2
#define MOTOR1_PWM_CHANNEL TIM_CHANNEL_1
#define MOTOR1_PWM_MAX 1000
#define MOTOR1_A_GPIO GPIOC
#define MOTOR1_A_PIN GPIO_PIN_7
#define MOTOR1_B_GPIO GPIOC
#define MOTOR1_B_PIN GPIO_PIN_8
void Motor_Init(void) //电机初始化
{
    HAL_TIM_PWM_Start(&MOTOR1_PWM, MOTOR1_PWM_CHANNEL);
}
void Motor_Forward(int forward) //设置方向
{
    if(forward > 0)//前进
    {
        HAL_GPIO_WritePin(MOTOR1_B_GPIO, MOTOR1_A_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MOTOR1_B_GPIO, MOTOR1_B_PIN, GPIO_PIN_RESET);
    }
    else if(forward < 0)//后退
    {
        HAL_GPIO_WritePin(MOTOR1_A_GPIO, MOTOR1_A_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR1_B_GPIO, MOTOR1_B_PIN, GPIO_PIN_SET);
    }
    else//停止
    {
        HAL_GPIO_WritePin(MOTOR1_A_GPIO, MOTOR1_A_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MOTOR1_B_GPIO, MOTOR1_B_PIN, GPIO_PIN_RESET);
    }
}
void Motor_SetSpeed(float speed) //设置占空比
{
    if (speed < 0){
        Motor_Forward(-1);
        speed = -speed;
    }
    else if (speed > 0){
        Motor_Forward(1);
    }
    else 
        Motor_Forward(0);
    __HAL_TIM_SET_COMPARE(&MOTOR1_PWM, MOTOR1_PWM_CHANNEL,(uint8_t)speed);
}