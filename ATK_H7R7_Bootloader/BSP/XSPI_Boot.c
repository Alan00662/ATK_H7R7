#include "XSPI_Boot.h"
#include "usart.h"
/* ����ȫ���жϵĺ� */
#define ENABLE_INT()	__set_PRIMASK(0)	/* ʹ��ȫ���ж� */
#define DISABLE_INT()	__set_PRIMASK(1)	/* ��ֹȫ���ж� */

void Boot_JumpToApp(void)
{
	uint32_t i=0;
	void (*AppJump)(void);         /* ����һ������ָ�� */
	__IO uint32_t AppAddr = FLASH_MEM_ADDR;  /* APP ��ַ */
	printf_tx1("Boot Start Jump To App....");
    /* �ر�ȫ���ж� */
	DISABLE_INT(); 
    
    /* ��������ʱ�ӵ�Ĭ��״̬��ʹ��HSIʱ�� */
	HAL_RCC_DeInit();
    
	/* �رյδ�ʱ������λ��Ĭ��ֵ */
	SysTick->CTRL = 0;
  SysTick->LOAD = 0;
  SysTick->VAL = 0;

	/* �ر������жϣ���������жϹ����־ */
	for (i = 0; i < 8; i++)
	{
		NVIC->ICER[i]=0xFFFFFFFF;
		NVIC->ICPR[i]=0xFFFFFFFF;
	}	

	/* ʹ��ȫ���ж� */
	ENABLE_INT();

	/* ��ת��Ӧ�ó����׵�ַ��MSP����ַ+4�Ǹ�λ�жϷ�������ַ */
	AppJump = (void (*)(void)) (*((uint32_t *) (AppAddr + 4)));

	/* ��������ջָ�� */
	__set_MSP(*(uint32_t *)AppAddr);
	
	/* ��RTOS���̣�����������Ҫ������Ϊ��Ȩ��ģʽ��ʹ��MSPָ�� */
	__set_CONTROL(0);

	/* ��ת��ϵͳBootLoader */
	AppJump(); 

	/* ��ת�ɹ��Ļ�������ִ�е�����û�������������Ӵ��� */
//	while (1)
//	{
//		HAL_Delay(300);
//		HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin);
//	}
}

