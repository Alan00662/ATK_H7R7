#ifndef _BSP_H_
#define _BSP_H_


/* CPU空闲时执行的函数 */


/* 开关全局中断的宏 */
#define ENABLE_INT()	__set_PRIMASK(0)	/* 使能全局中断 */
#define DISABLE_INT()	__set_PRIMASK(1)	/* 禁止全局中断 */




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

/* 定义优先级分组 */
#define NVIC_PREEMPT_PRIORITY	4




void MPU_Config(void);
/* 提供给其他C文件调用的函数 */
int SystemClock_Config(void);

#endif
