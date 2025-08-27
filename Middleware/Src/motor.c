#include "motor.h"

#define MOTOR1_PWM htim2
#define MOTOR1_PWM_CHANNEL TIM_CHANNEL_1

void Motor_Init(void) //????
{
    HAL_TIM_PWM_Start(&MOTOR1_PWM, MOTOR1_PWM_CHANNEL);
}
void Motor_SetSpeed(int speed) //??????
{
    if (speed < 0) {
        speed = 0; // ???????0
    } else if (speed > 100) {
        speed = 100; // ???????100
    }    
    __HAL_TIM_SET_COMPARE(&MOTOR1_PWM, MOTOR1_PWM_CHANNEL, speed);
}