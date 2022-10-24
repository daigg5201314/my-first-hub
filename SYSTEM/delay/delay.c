/*
 * Project: 1.LED
 * Module: 系统延时
 * File: delay.c
 * Created Date: 2022-10-24 20:11:18
 * Author: 堡烨
 * Description: 系统延时(毫秒级别和微秒级别)
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
#include "delay.h"
#include "sys.h"
#if SYSTEM_SUPPORT_UCOS
#include "includes.h" //ucos使用的头文件
#endif
/* ======================================================================================
 * macros(宏指令)
 */

/* ======================================================================================
 * types(变量类型)
 */

/* ======================================================================================
 * declaration(函数声明)
 */

/* ======================================================================================
 * globals(全局函数/变量)
 */
static u8 fac_us = 0;  // us延时被乘数
static u16 fac_ms = 0; // ms延时被乘数
/* ======================================================================================
 * helper(帮助函数)
 */

/* ======================================================================================
 * private implementation(内部使用函数)
 */

/* ======================================================================================
 * implementation(全局使用函数)
 */

#ifdef OS_CRITICAL_METHOD
/**
 * @brief :系统时钟中断函数
 * @param :void
 * @return :void
 */
void SysTick_Handler(void)
{
	OSIntEnter(); //进入中断
	OSTimeTick(); //调用ucos的始终服务程序
	OSIntExit();  //触发任务切换软中断
}
#endif

/**
 * @brief :初始化延时函数
 * @param :void
 * @return :void
 */
void delay_init()
{
#ifdef OS_CRITICAL_METHOD
	u32 reload;
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //选择外部时钟
	fac_us = SystemCoreClock / 8000000;					  //采用八分频，为系统时钟的1/8
#ifdef OS_CRITICAL_METHOD
	reload = SystemCoreClock / 8000000;
	reload *= 1000000 / OS_TICKS_PER_SEC;

	fac_ms = 1000 / OS_TICKS_PER_SEC;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->LOAD = reload;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#else
	fac_ms = (u16)fac_us * 1000; //在非ucos下，代表每个ms需要的systick的计数值
#endif
}

#ifdef OS_CRITICAL_METHOD
/**
 * @brief :延时微秒函数
 * @param nus:需要延时的us数值
 * @return :void
 */
void delay_us(u32 nus)
{
	u32 ticks;
	u32 told, tnow, tcnt = 0;
	u32 reload = SysTick->LOAD; // LOAD的值相当于周期的值
	ticks = nus * fac_us;		//需要的节拍数
	tcnt = 0;
	told = SysTick->VAL; //刚进入的时的计数值
	while (1)
	{
		tnow = SysTick->VAL;
		if (tnow != told)
		{
			if (tnow < told)
				tcnt += told - tnow; // SYSTICK是一个递减的数值
			else
				tcnt += reload - tnow + told;
			told = tnow;
			if (tcnt >= ticks)
				break; //超过时间退出
		}
	};
}

/**
 * @brief :延时毫秒函数
 * @param nms:需要延时的ms数值
 * @return :void
 */
void delay_ms(u16 nms)
{
	if (OSRunning == TRUE) //如果os已经在跑了
	{
		if (nms >= fac_ms) //延时的时间大于ucos的最少时间周期
		{
			OSTimeDly(nms / fac_ms); // ucos延时
		}
		nms %= fac_ms; // ucos已经无法提供这么小的延时了，采用普通方式延时
	}
	delay_us((u32)(nms * 1000)); //普通方式延时，此时的ucos无法启动调度
#else
/**
 * @brief :延时微秒函数
 * @param nus:需要延时的us数值
 * @return :void
 */
void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus * fac_us;			  //时间加载
	SysTick->VAL = 0x00;					  //清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16))); //等待时间到达，bit16置1说明时间到，跳出循环
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	  //关闭计数器
	SysTick->VAL = 0X00;						  //清空计数器
}

/**
 * @brief :延时毫秒函数
 * @param nms:需要延时的ms数值
 * @return :void
 */
void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = (u32)nms * fac_ms;		  //时间加载
	SysTick->VAL = 0x00;					  //清空计数值
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
	do
	{
		temp = SysTick->CTRL;
	} while (temp & 0x01 && !(temp & (1 << 16))); //等待时间到达
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	  //关闭计数
	SysTick->VAL = 0X00;						  //清空计数值
}
#endif
