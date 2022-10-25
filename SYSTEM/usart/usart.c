/*
 * Project: 1.LED
 * Module: �����շ�ģ��
 * File: usart.c
 * Created Date: 2022-10-24 20:49:47
 * Author: ����
 * Description: �����շ�ģ��
 * -----
 * todo: modified
 * -----
 * Copyright (c) 2022 - vDiscovery, Inc
 */

/* ======================================================================================
 * log(��־ģ��)
 */
#define LOG_ENABLE_DEBUG (1)

/* ======================================================================================
 * includes(ͷ�ļ�����)
 */
#include "usart.h"
#if SYSTEM_SUPPORT_UCOS
#include "includes.h" //ucos
#endif
/* ======================================================================================
 * macros(��ָ��)
 */

/* ======================================================================================
 * types(��������)
 */
#if EN_USART1_RX				//ʹ�ô��ڽ���ʹ��
u8 USART_RX_BUF[USART_REC_LEN]; //���ջ��壬���USART_REC_LEN���ֽ�
u16 USART_RX_STA = 0;			//����״̬���
#endif
/* ======================================================================================
 * declaration(��������)
 */

/* ======================================================================================
 * globals(ȫ�ֺ���/����)
 */

/* ======================================================================================
 * helper(��������)
 */
#if 1
#pragma import(__use_no_semihosting)
//��׼����Ҫ��֧�ֺ���
struct __FILE
{
	int handle;
};

FILE __stdout;
//����_sys_exit()�ѱ������ð�����ģʽ
_sys_exit(int x)
{
	x = x;
}
//�ض���fputc����
int fputc(int ch, FILE *f)
{
	while ((USART1->SR & 0X40) == 0)
		; //ѭ������ֱ���������
	USART1->DR = (u8)ch;
	return ch;
}
#endif
/* ======================================================================================
 * private implementation(�ڲ�ʹ�ú���)
 */

/* ======================================================================================
 * implementation(ȫ��ʹ�ú���)
 */

#if EN_USART1_RX //ʹ�ô��ڽ���ʹ��
/**
 * @brief :���ڳ�ʼ������
 * @param bound:���ڲ�����
 * @return :void
 */
void uart_init(u32 bound)
{
	// GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //ʹ��USART1��GPIOAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;									  // PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //�ж����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //����ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQ�ж�ʹ��
	NVIC_Init(&NVIC_InitStructure);							  //��ʼ��NVIC

	// USART ?????????

	USART_InitStructure.USART_BaudRate = bound;										//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						//�ֳ�Ϊ8λ�����ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							//����ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure);	   //��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�����ж�
	USART_Cmd(USART1, ENABLE);					   //ʹ�ܴ���
}

/**
 * @brief :����1�ж�
 * @param :void
 * @return :void
 */
void USART1_IRQHandler(void) //����1�жϺ���
{
	u8 Res;
#ifdef OS_TICKS_PER_SEC //ʹ��ucosll
	OSIntEnter();
#endif
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����ж�(�������ݱ�����0x0d 0x0a��β)
	{
		Res = USART_ReceiveData(USART1); //(USART1->DR);	//��ȡ���յ�������

		if ((USART_RX_STA & 0x8000) == 0) //����δ���
		{
			if (USART_RX_STA & 0x4000) //���յ���0x0d
			{
				if (Res != 0x0a)
					USART_RX_STA = 0; //���մ������¿�ʼ
				else
					USART_RX_STA |= 0x8000; //���������
			}
			else //��û���յ�0X0D
			{
				if (Res == 0x0d)
					USART_RX_STA |= 0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA & 0X3FFF] = Res;
					USART_RX_STA++;
					if (USART_RX_STA > (USART_REC_LEN - 1))
						USART_RX_STA = 0; //�������ݴ������¿�ʼ����
				}
			}
		}
	}
#ifdef OS_TICKS_PER_SEC //ʹ��ucosll.
	OSIntExit();
#endif
}
#endif
