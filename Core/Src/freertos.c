/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "font.h"
#include "ZDTcontrol.h"
#include "string.h"
#include "stdio.h"
#include "pid.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern pid_t pid1;
extern float speed_Control;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void OLED_Task(void *pvParameters);
void ZDT_Task( void *pvParameters);
void motor_Task(void *pvParameters);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
TaskHandle_t OLEDTask = NULL;
TaskHandle_t ZDTTask = NULL;
TaskHandle_t motorHandle = NULL;

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  taskENTER_CRITICAL();

  xTaskCreate(
    OLED_Task,              /* 任务函数 */
    "OLEDTask",                   /* 任务名称（用于调试） */
    128,                        /* 堆栈大小（以字为单位） */
    NULL,                       /* 传递给任务函数的参数 */
    2,                          /* 任务优先级 */
    &OLEDTask            /* 任务句柄 */
  );

  xTaskCreate(
    ZDT_Task,              /* 任务函数 */
    "ZDTTask",                   /* 任务名称（用于调试） */
    128,                        /* 堆栈大小（以字为单位） */
    NULL,                       /* 传递给任务函数的参数 */
    2,                          /* 任务优先级 */
    &ZDTTask           /* 任务句柄 */
  );

  xTaskCreate(
    motor_Task,              /* 任务函数 */
    "motorTask",                   /* 任务名称（用于调试） */
    128,                        /* 堆栈大小（以字为单位） */
    NULL,                       /* 传递给任务函数的参数 */
    4,                          /* 任务优先级 */
    &motorHandle            /* 任务句柄 */
  );

  taskEXIT_CRITICAL();
  vTaskDelete(NULL);
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void OLED_Task( void *pvParameters )//用来OLED显示PID参数
{
  for(;;)
  {
    char a[20]={0};
    char pidnumber[20]={0};
    char pidtarget[10]={0};
    char piderror[10]={0};
    char pidout[10]={0};
    sprintf(pidnumber,"kp:%.d ki:%.1f kd:%.1f",Encoder1_Position(), pid1.pid_i, pid1.pid_d);
    sprintf(a,"S:%.1f",speed_Control);
    sprintf(pidtarget,"t:%.1f",pid1.target);
    sprintf(piderror,"e:%.1f",pid1.error0);
    sprintf(pidout,"o:%.1f",pid1.out);
    OLED_NewFrame();
    OLED_PrintASCIIString(1,1,pidnumber,&afont12x6,OLED_COLOR_NORMAL);
    OLED_PrintASCIIString(1,12,a,&afont12x6,OLED_COLOR_NORMAL);
    OLED_PrintASCIIString(1,24,pidtarget,&afont12x6,OLED_COLOR_NORMAL);
    OLED_PrintASCIIString(1,36,piderror,&afont12x6,OLED_COLOR_NORMAL);
    OLED_PrintASCIIString(1,48,pidout,&afont12x6,OLED_COLOR_NORMAL);
    OLED_ShowFrame();
    vTaskDelay(10);
  }
}
void ZDT_Task( void *pvParameters ) //暂且不用
{
  for(;;)
  {
    
  }
}

void motor_Task( void *pvParameters )
{
  for(;;)
  {
    pid1.target = speed_Control;
    pid_update(&pid1);
    Motor_SetSpeed(pid1.out);
    vTaskDelay(10);
  }
}

/* USER CODE END Application */
