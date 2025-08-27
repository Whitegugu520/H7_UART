#include "MYUART.h"


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void MY_UART_Init()
{
    // huart1.Instance = USART1;
    // huart1.Init.BaudRate = 115200;
    // huart1.Init.WordLength = UART_WORDLENGTH_8B;
    // huart1.Init.StopBits = UART_STOPBITS_1;
    // huart1.Init.Parity = UART_PARITY_NONE;
    // huart1.Init.Mode = UART_MODE_TX_RX;
    // huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    // huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    // huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    // huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  
    // // H7系列需要配置USART时钟源
    // __HAL_RCC_USART1_CLK_ENABLE();
    // RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
    // PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    // PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_PCLK2;
    // HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);
}

void UART2_TX(char *data,size_t size)
{
    HAL_UART_Transmit_IT(&huart2, (uint8_t *)data,size);
}
// void UART2_RX(char *buffer, size_t size)
// {
//     HAL_UART_Receive(&huart2, (uint8_t *)buffer, size, HAL_MAX_DELAY);
// }