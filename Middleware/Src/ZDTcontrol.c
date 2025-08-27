#include "ZDTcontrol.h"


uint8_t message[30] = {0};
uint8_t message_size = 0;

//内部函数，用于和MYUART中的UART_TX相接，将控制信号发送给电机
//TODO串口筛选尚未完成
void ZDT_Control_TX()      
{  
    UART2_TX((char *)message,message_size);
}
//用来使能电机  1 enable 0 disable
void ZDT_Control_able(uint8_t add,uint8_t able)     
{
 
    uint8_t sitting[]={0x01,0xf3,0xab,0x00,0x01,0x6B};
    sitting[0] = add; //地址
    sitting[3] = able; //使能
    memcpy(message,sitting,sizeof(sitting));
    message_size = sizeof(sitting);
    ZDT_Control_TX();
}
//速度模式控制 地址 + 0xF6 + 方向 + 速度 + 加速度 + 多机同步标志 + 校验字节
//01表示旋转方向为CCW（00表示CW），05 DC表示速度为0x05DC = 1500(RPM)，0A 表示加速度档位为0x0A=10，00表示不启用多机同步（01表示启用）
void ZDT_Control_speed(uint8_t add,uint8_t dir,uint16_t speed,uint8_t acc)        //TODO多机同步已完成
{
    uint8_t sitting[]={0x01,0xf6,0x00,0x00,0x00,0x00,0x01,0x6B};
    sitting[0] = add; //地址
    sitting[2] = dir;
    sitting[3] = (speed >> 8) & 0xff;
    sitting[4] = (uint8_t)(speed & 0xff);
    sitting[5] = acc;
    memcpy(message,sitting,sizeof(sitting));
    message_size = sizeof(sitting);
    ZDT_Control_TX();
}
//位置模式控制 地址 +0xFD+ 方向 + 速度+ 加速度 + 脉冲数 + 相对/绝对模式标志 +多机同步标志 + 校验字节
void ZDT_Control_position(uint8_t add,uint8_t dir, uint16_t speed, uint8_t acc, uint32_t pulse, uint8_t mode)
{
    uint8_t sitting[]={0x01,0xfd,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x6b};
    sitting[0] = add; // 地址
    sitting[2] = dir;
    sitting[3] = (speed >> 8) & 0xff;
    sitting[4] = (uint8_t)(speed & 0xff);
    sitting[5] = acc;
    sitting[6] = (pulse >> 24) & 0xff;
    sitting[7] = (pulse >> 16) & 0xff;
    sitting[8] = (pulse >> 8) & 0xff;
    sitting[9] = (uint8_t)(pulse & 0xff);
    sitting[10] = mode; // 0 相对位置, 1 绝对位置
    memcpy(message,sitting,sizeof(sitting));
    message_size = sizeof(sitting);
    ZDT_Control_TX();
}
void ZDT_Control_stop(uint8_t add)          //速度模式控制 地址 + 0xF6 + 方向 + 速度 + 加速度 + 多机同步标志 + 校验字节
{
    uint8_t sitting[]={0x00,0xfe,0x98,0x01,0x6b};
    sitting[0] = add; //地址
    memcpy(message,sitting,sizeof(sitting));
    message_size = sizeof(sitting);
    ZDT_Control_TX();
}
void ZDT_Control_move(uint8_t add)          //速度模式控制 地址 + 0xF6 + 方向 + 速度 + 加速度 + 多机同步标志 + 校验字节
{
    uint8_t sitting[]={0x00,0xff,0x66,0x6b};
    sitting[0] = add; //地址
    memcpy(message,sitting,sizeof(sitting));
    message_size = sizeof(sitting);
    ZDT_Control_TX();
}
uint32_t ZDT_Pulse(float number)            //将圈数换成脉冲数
{
    return (uint32_t)(number * 1500);
}