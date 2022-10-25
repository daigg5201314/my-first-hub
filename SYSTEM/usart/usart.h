/*
 * Project: 1.LED
 * Module: 串口收发模块
 * File: usart.h
 * Created Date: 2022-10-25 16:23:38
 * Author: 堡烨
 * Description: 串口收发模块
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */
#ifndef USART_H
#define USART_H

/* ======================================================================================
 * includes(头文件包含)
 */
#include "stdio.h"
#include "sys.h"
/* ======================================================================================
 * macros(宏指令)
 */
#define USART_REC_LEN 200 //定义接收最大字节数 200
#define EN_USART1_RX 1    // 1：使能，0：禁止使能
/* ======================================================================================
 * types(变量类型)
 */
extern u8 USART_RX_BUF[USART_REC_LEN]; //接收缓冲，最大为USART_REC_LEN个字节
extern u16 USART_RX_STA;               //接收状态标记
/* ======================================================================================
 * declaration(函数声明)
 */

void uart_init(u32 bound);
#endif // _USART_H
