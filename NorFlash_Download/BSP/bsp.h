#ifndef _BSP_H_
#define _BSP_H_


/* CPU����ʱִ�еĺ��� */


/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */




#define ERROR_HANDLER()		Error_Handler(__FILE__, __LINE__);


#include "stm32h7rsxx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef TRUE
	#define TRUE  1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

/* �������ȼ����� */
#define NVIC_PREEMPT_PRIORITY	4




void MPU_Config(void);
/* �ṩ������C�ļ����õĺ��� */
int SystemClock_Config(void);

#endif
