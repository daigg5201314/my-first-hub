/*
 * Project: 1.LED
 * Module: module_name
 * File: main.c
 * Created Date: 2022-10-24 14:25:45
 * Author: 堡烨
 * Description: description
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */

/* ======================================================================================
 * log(日志模块)
 */
#define LOG_ENABLE_DEBUG (1)

/* ======================================================================================
 * includes(头文件包含)
 */
#include "base.h"
#include "usart.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "platform_config.h"
/* ===================== =================================================================
 * macros(宏指令)
 */

/* ======================================================================================
 * types(变量类型)
 */
TaskHandle_t StartTask_Handler;
TaskHandle_t LED0Task_Handler;
TaskHandle_t LED1Task_Handler;

/* ======================================================================================
 * declaration(函数声明)
 */
void start_task(void *pvParameters);
void led0_task(void *pvParameters);
void led1_task(void *pvParameters);
/* ======================================================================================
 * globals(全局函数/变量)
 */

/* ======================================================================================
 * helper(帮助函数)
 */

/* ======================================================================================
 * private implementation(内部使用函数)
 */

//开始任务任务函数
static void start_task(void *pvParameters)
{
	taskENTER_CRITICAL(); //进入临界区
	//创建LED0任务
	xTaskCreate((TaskFunction_t)led0_task,
				(const char *)"led0_task",
				(uint16_t)LED0_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)LED0_TASK_PRIO,
				(TaskHandle_t *)&LED0Task_Handler);
	//创建LED1任务
	xTaskCreate((TaskFunction_t)led1_task,
				(const char *)"led1_task",
				(uint16_t)LED1_STK_SIZE,
				(void *)NULL,
				(UBaseType_t)LED1_TASK_PRIO,
				(TaskHandle_t *)&LED1Task_Handler);
	vTaskDelete(StartTask_Handler); //删除开始任务
	taskEXIT_CRITICAL();			//退出临界区
}

// LED0任务函数
static void led0_task(void *pvParameters)
{
	while (1)
	{
		// LED0 = ~LED0;
		printf("led0_task\r\n");
		vTaskDelay(500);
	}
}

// LED1任务函数
static void led1_task(void *pvParameters)
{
	while (1)
	{
		// LED1 = 0;
		// vTaskDelay(200);
		// LED1 = 1;
		printf("led1_task\r\n");
		vTaskDelay(800);
	}
}
/* ======================================================================================
 * implementation(全局使用函数)
 */
int main(void)
{
	printf("main start\r");
	NVIC_Configuration(2); //设置系统中断优先级分组2
	delay_init();		   //延时函数初始化
	uart_init(9600);	   //初始化串口
	//创建开始任务
	xTaskCreate((TaskFunction_t)start_task,			 //任务函数
				(const char *)"start_task",			 //任务名称
				(uint16_t)START_STK_SIZE,			 //任务堆栈大小
				(void *)NULL,						 //传递给任务函数的参数
				(UBaseType_t)START_TASK_PRIO,		 //任务优先级
				(TaskHandle_t *)&StartTask_Handler); //任务句柄
	vTaskStartScheduler();							 //开启任务调度
}
