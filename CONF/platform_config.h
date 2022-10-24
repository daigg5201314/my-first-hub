/*
 * Project: 1.LED
 * Module: 系统配置
 * File: platform_config.h
 * Created Date: 2022-10-24 14:14:59
 * Author: 堡烨
 * Description: description
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */
#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H

/* ======================================================================================
 * includes(头文件包含)
 */
#include "base.h"

/* ======================================================================================
 * macros(宏指令)
 */
//任务优先级
#define START_TASK_PRIO 1
//任务堆栈大小
#define START_STK_SIZE 128
//任务优先级
#define LED0_TASK_PRIO 2
//任务堆栈大小
#define LED0_STK_SIZE 50
//任务优先级
#define LED1_TASK_PRIO 3
//任务堆栈大小
#define LED1_STK_SIZE 50
/* ======================================================================================
 * types(变量类型)
 */

/* ======================================================================================
 * declaration(函数声明)
 */

#endif // PLATFORM_CONFIG_H