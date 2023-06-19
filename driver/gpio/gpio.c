/*
 * Project: 1.LED
 * Module: user_gpio.c
 * File: gpio.c
 * Created Date: 2022-10-25 19:14:01
 * Author: 堡烨
 * Description: 用户使用的GPIO封装函数接口
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
#include "gpio.h"

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
 * @brief :GPIO初始化函数
 * @param gpio:gpio初始化结构体
 * @return :void
 */
void user_gpio_init(user_gpio_t gpio)
{
    GPIO_InitTypeDef gpio_info;
    RCC_APB2PeriphClockCmd(gpio.user_gpio_zone, true); // 使能GPIO时钟
    gpio_info.GPIO_Pin = gpio.user_gpio_pin;
    gpio_info.GPIO_Speed = gpio.user_gpio_speed;
    gpio_info.GPIO_Mode = gpio.user_gpio_mode;
    GPIO_Init(&gpio.user_gpio_select, &gpio_info);
}

/**
 * @brief :GPIO写函数
 * @param port:gpio分区
 * @param pin:gpio引脚
 * @param is_high:拉高拉低操作
 * @return :void
 */
void user_gpio_write(GPIO_TypeDef port, uint16_t pin, uint8_t is_high)
{
    GPIO_WriteBit(&port, pin, is_high);
}

/**
 * @brief :GPIO读函数
 * @param port:gpio分区
 * @param pin:gpio引脚
 * @return :uint8_t
 */
uint8_t user_gpio_read(GPIO_TypeDef port, uint16_t pin)
{
    return GPIO_ReadOutputDataBit(&port, pin);
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {

        EXTI_ClearITPendingBit(EXTI_Line0);
        printf("111");
    }
}