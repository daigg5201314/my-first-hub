/*
 * Project: 1.LED
 * Module: 串口收发模块
 * File: usart.c
 * Created Date: 2022-10-24 20:49:47
 * Author: 堡烨
 * Description: 串口收发模块
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
#include "usart.h"
#if SYSTEM_SUPPORT_UCOS
#include "includes.h" //ucos
#endif
/* ======================================================================================
 * macros(宏指令)
 */

/* ======================================================================================
 * types(变量类型)
 */
#if EN_USART1_RX				//使用串口接收使能
u8 USART_RX_BUF[USART_REC_LEN]; //接受缓冲，最大USART_REC_LEN个字节
u16 USART_RX_STA = 0;			//接受状态标记
#endif
/* ======================================================================================
 * declaration(函数声明)
 */

/* ======================================================================================
 * globals(全局函数/变量)
 */

/* ======================================================================================
 * helper(帮助函数)
 */
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
//定义_sys_exit()已避免是用半主机模式
_sys_exit(int x)
{
	x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
	while ((USART1->SR & 0X40) == 0)
		; //循环发送直到发送完毕
	USART1->DR = (u8)ch;
	return ch;
}
#endif
/* ======================================================================================
 * private implementation(内部使用函数)
 */

/* ======================================================================================
 * implementation(全局使用函数)
 */

#if EN_USART1_RX //使用串口接收使能
/**
 * @brief :串口初始化函数
 * @param bound:串口波特率
 * @return :void
 */
void uart_init(u32 bound)
{
	// GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //使能USART1，GPIOA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;									  // PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Usart1 NVIC 配置

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //中断优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //子抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ中断使能
	NVIC_Init(&NVIC_InitStructure);							  //初始化NVIC

	// USART ?????????

	USART_InitStructure.USART_BaudRate = bound;										//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//字长为8位的数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//设置停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;								//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式

	USART_Init(USART1, &USART_InitStructure);	   //初始化串口
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //开启中断
	USART_Cmd(USART1, ENABLE);					   //使能串口
}

/**
 * @brief :串口1中断
 * @param :void
 * @return :void
 */
void USART1_IRQHandler(void) //????1?ж???????
{
	u8 Res;
#ifdef OS_TICKS_PER_SEC //?????????????????,???????ucosII??.
	OSIntEnter();
#endif
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //?????ж?(????????????????0x0d 0x0a??β)
	{
		Res = USART_ReceiveData(USART1); //(USART1->DR);	//??????????????

		if ((USART_RX_STA & 0x8000) == 0) //????δ???
		{
			if (USART_RX_STA & 0x4000) //???????0x0d
			{
				if (Res != 0x0a)
					USART_RX_STA = 0; //???????,??????
				else
					USART_RX_STA |= 0x8000; //?????????
			}
			else //??????0X0D
			{
				if (Res == 0x0d)
					USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res;
					USART_RX_STA++;
					if (USART_RX_STA > (USART_REC_LEN - 1))
						USART_RX_STA = 0; //???????????,??????????
				}
			}
		}
	}
#ifdef OS_TICKS_PER_SEC //?????????????????,???????ucosII??.
	OSIntExit();
#endif
}
#endif
