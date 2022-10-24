/*
 * Project: 1.LED
 * Module: 系统相关的定义
 * File: sys.h
 * Created Date: 2022-10-24 20:03:51
 * Author: 堡烨
 * Description: 系统相关的定义
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */
#ifndef SYS_H
#define SYS_H

/* ======================================================================================
 * includes(头文件包含)
 */
#include "stm32f10x.h"
/* ======================================================================================
 * macros(宏指令)
 */
#define SYSTEM_SUPPORT_UCOS 0 //定义系统文件是否支持ucos 0不支持，1支持

// IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

// IO口地址映射
#define GPIOA_ODR_Addr (GPIOA_BASE + 12) // 0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE + 12) // 0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE + 12) // 0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE + 12) // 0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE + 12) // 0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE + 12) // 0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE + 12) // 0x40011E0C

#define GPIOA_IDR_Addr (GPIOA_BASE + 8) // 0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE + 8) // 0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE + 8) // 0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE + 8) // 0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE + 8) // 0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE + 8) // 0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE + 8) // 0x40011E08

#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) //
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)	 //

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) //
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)	 //

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) //
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)	 //

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) //
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)	 //

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) //
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)	 //

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) //
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)	 //

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) //
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)	 //
/* ======================================================================================
 * types(变量类型)
 */
typedef enum
{
	PRIORITY_0,
	PRIORITY_1,
	PRIORITY_2,
	PRIORITY_3,
	PRIORITY_4,
} nvic_conf_e;
/* ======================================================================================
 * declaration(函数声明)
 */
/**
 * @brief :设置系统中断优先级
 * @param priority:任务优先级
 * @return :void
 */
void NVIC_Configuration(nvic_conf_e priority);
#endif // _SYS_H
