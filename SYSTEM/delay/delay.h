/*
 * Project: 1.LED
 * Module: 系统延时
 * File: delay.h
 * Created Date: 2022-10-24 20:31:33
 * Author: 堡烨
 * Description: 系统延时
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */
#ifndef DELAY_H
#define DELAY_H

/* ======================================================================================
 * includes(头文件包含)
 */
#include "sys.h"

/* ======================================================================================
 * macros(宏指令)
 */

/* ======================================================================================
 * types(变量类型)
 */

/* ======================================================================================
 * declaration(函数声明)
 */
void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif // _DELAY_H
