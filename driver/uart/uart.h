/*
 * Project: 1.LED
 * Module: USER
 * File: uart.h
 * Created Date: 2022-10-25 16:32:09
 * Author: 堡烨
 * Description: 用户使用的串口封装函数接口
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */
#ifndef USER_UART_H
#define USER_UART_H

/* ======================================================================================
 * includes(头文件包含)
 */
#include "base.h"
#include "usart.h"
/* ======================================================================================
 * macros(宏指令)
 */
#define UART_1 USART1
#define UART_2 USART2
#define UART_3 USART3
/* ======================================================================================
 * types(变量类型)
 */
typedef enum
{
    USER_UART_1 = 37,
    USER_UART_2,
} user_uart_mode_e; //定义两路串口

typedef enum
{
    USER_UART_RX = 4u,
    USER_URAT_TX = 8u,
} user_uart_tx_rx_e;

typedef enum
{
    UART_SPEED_10MHz = 1,
    UART_SPEED_2MHz,
    UART_SPEED_50MHz
} user_uart_speed_e;

typedef struct
{
    user_uart_mode_e uart_select; //使用串口选择
    uint16_t uart_pin;            //串口的pin脚
    user_uart_speed_e uart_speed; //串口通信速率
    uint8_t uart_mode;            //串口通信模式
    uint8_t uart_baud;            //串口通信的波特率
    uint8_t uart_wordlength;      //串口通信的字节长度
    uint8_t uart_stopbits;        //串口通信的停止位
    uint8_t uart_parity;          //串口通信的奇偶校验位
    user_uart_tx_rx_e uart_mode_RX;
    user_uart_tx_rx_e uart_mode_TX;
} user_uart_t;
/* ======================================================================================
 * declaration(函数声明)
 */

#endif // USER_UART_H