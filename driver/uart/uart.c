/*
 * Project: 1.LED
 * Module: user_uart.c
 * File: uart.c
 * Created Date: 2022-10-25 16:30:02
 * Author: 堡烨
 * Description: 用户使用的串口封装函数接口
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
#include "uart.h"

/* ======================================================================================
 * macros(宏指令)
 */

/* ======================================================================================
 * types(变量类型)
 */

/* ======================================================================================
 * declaration(函数声明)
 */
static user_uart_t g_uart_conf[] = {
    {
        USER_UART_1,
        GPIO_Pin_9,
        UART_SPEED_50MHz,
        GPIO_Mode_AF_PP,

    }};
/* ======================================================================================
 * globals(全局函数/变量)
 */

/* ======================================================================================
 * helper(帮助函数)
 */

/* ======================================================================================
 * private implementation(内部使用函数)
 */

/* ======================================================================================
 * implementation(全局使用函数)
 */

/**
 * @brief :串口中断服务配置
 * @param uart_sec:串口选择
 * @return :void
 */
void
user_uart_irq_request(user_uart_mode_e uart_sec)
{

    NVIC_InitTypeDef nvic_init;
    nvic_init.NVIC_IRQChannel = uart_sec;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 3; //
    nvic_init.NVIC_IRQChannelSubPriority = 3;        //
    nvic_init.NVIC_IRQChannelCmd = true;             //
    NVIC_Init(&nvic_init);                           //
}

/**
 * @brief :串口初始化操作
 * @param user_init:串口初始化结构体
 * @return :void
 */
void user_uart_init(user_uart_t user_init)
{
    GPIO_InitTypeDef gpio_init;
    USART_InitTypeDef uart_init;
    gpio_init.GPIO_Pin = user_init.uart_pin;
    gpio_init.GPIO_Speed = user_init.uart_speed;
    gpio_init.GPIO_Mode = user_init.uart_mode;
    uart_init.USART_BaudRate = user_init.uart_baud;
    uart_init.USART_WordLength = user_init.uart_wordlength;
    uart_init.USART_StopBits = user_init.uart_stopbits;
    uart_init.USART_Parity = user_init.uart_parity;
    uart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
    uart_init.USART_Mode = user_init.uart_mode_RX | user_init.uart_mode_TX;
    user_uart_irq_request(user_init.uart_select);
    GPIO_Init(GPIOA, &gpio_init);
    USART_Init(UART_1, &uart_init);
    USART_ITConfig(UART_1, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART_1, ENABLE);
}
