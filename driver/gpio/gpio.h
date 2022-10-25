/*
 * Project: 1.LED
 * Module: USER
 * File: gpio.h
 * Created Date: 2022-10-25 19:14:40
 * Author: 堡烨
 * Description: 用户使用的GPIO封装函数接口
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */
#ifndef USER_GPIO_H
#define USER_GPIO_H

/* ======================================================================================
 * includes(头文件包含)
 */
#include "base.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
/* ======================================================================================
 * macros(宏指令)
 */
void (*gpio_callback)(void);
/* ======================================================================================
 * types(变量类型)
 */
typedef enum
{
    USER_GPIOA = 4,
    USER_GPIOB = 8,
    USER_GPIOC = 16,
    USER_GPIOD = 32,
    USER_GPIOE = 64,
} user_gpio_e;

typedef struct
{
    GPIO_TypeDef user_gpio_select;     //配置gpio分区
    user_gpio_e user_gpio_zone;        //配置gpio分区
    uint16_t user_gpio_pin;            //配置的gpio引脚
    GPIOSpeed_TypeDef user_gpio_speed; //配置gpio速度
    GPIOMode_TypeDef user_gpio_mode;   //配置gpio模式
} user_gpio_t;
/* ======================================================================================
 * declaration(函数声明)
 */

#endif // USER_GPIO_H