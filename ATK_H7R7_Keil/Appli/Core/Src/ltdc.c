/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "ltdc.h"

/* USER CODE BEGIN 0 */
uint16_t g_ltdc_lcd_framebuf[1280][800] __attribute__((section(".bss.ARM.__at_0x70000000")));
uint16_t *g_ltdc_framebuf[2];
		
void BL_Init(void)
{
	  GPIO_InitTypeDef gpio_init_struct = {0};
	    /* ʹ��ʱ�� */
    LTDC_BL_GPIO_CLK_ENABLE();
	    /* ����LTDC LCD BL���� */
    gpio_init_struct.Pin = LTDC_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LTDC_BL_GPIO_PORT, &gpio_init_struct);
			
		LTDC_BL(1);
}
/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */
	g_ltdc_framebuf[0] = (uint16_t *)g_ltdc_lcd_framebuf;
  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 0;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 46;
  hltdc.Init.AccumulatedVBP = 23;
  hltdc.Init.AccumulatedActiveW = 846;
  hltdc.Init.AccumulatedActiveH = 503;
  hltdc.Init.TotalWidth = 1056;
  hltdc.Init.TotalHeigh = 525;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 255;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 800;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInit.LtdcClockSelection = RCC_LTDCCLKSOURCE_PLL3R;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PB5     ------> LTDC_R2
    PG0     ------> LTDC_R7
    PB3(JTDO/TRACESWO)     ------> LTDC_R4
    PG2     ------> LTDC_HSYNC
    PE11     ------> LTDC_VSYNC
    PA12     ------> LTDC_B2
    PA11     ------> LTDC_B3
    PB4(NJTRST)     ------> LTDC_R3
    PA9     ------> LTDC_B5
    PG1     ------> LTDC_R6
    PA10     ------> LTDC_B4
    PA8     ------> LTDC_B6
    PA15(JTDI)     ------> LTDC_R5
    PA2     ------> LTDC_B7
    PB12     ------> LTDC_G5
    PA0     ------> LTDC_G3
    PA1     ------> LTDC_G2
    PA5     ------> LTDC_CLK
    PD12     ------> LTDC_DE
    PB11     ------> LTDC_G6
    PB13     ------> LTDC_G4
    PB10     ------> LTDC_G7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_LTDC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_12|GPIO_PIN_11
                          |GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_LTDC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF11_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_8|GPIO_PIN_15
                          |GPIO_PIN_2|GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PB5     ------> LTDC_R2
    PG0     ------> LTDC_R7
    PB3(JTDO/TRACESWO)     ------> LTDC_R4
    PG2     ------> LTDC_HSYNC
    PE11     ------> LTDC_VSYNC
    PA12     ------> LTDC_B2
    PA11     ------> LTDC_B3
    PB4(NJTRST)     ------> LTDC_R3
    PA9     ------> LTDC_B5
    PG1     ------> LTDC_R6
    PA10     ------> LTDC_B4
    PA8     ------> LTDC_B6
    PA15(JTDI)     ------> LTDC_R5
    PA2     ------> LTDC_B7
    PB12     ------> LTDC_G5
    PA0     ------> LTDC_G3
    PA1     ------> LTDC_G2
    PA5     ------> LTDC_CLK
    PD12     ------> LTDC_DE
    PB11     ------> LTDC_G6
    PB13     ------> LTDC_G4
    PB10     ------> LTDC_G7
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_12
                          |GPIO_PIN_11|GPIO_PIN_13|GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOE, GPIO_PIN_11);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_9|GPIO_PIN_10
                          |GPIO_PIN_8|GPIO_PIN_15|GPIO_PIN_2|GPIO_PIN_0
                          |GPIO_PIN_1|GPIO_PIN_5);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_12);

  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
 * @brief   LTDC����
 * @param   x: ���X����
 * @param   y: ���Y����
 * @param   color: �����ɫ
 * @retval  ��
 */
void ltdc_draw_point(uint16_t x, uint16_t y, uint32_t color)
{

//    if (lcdltdc.dir == 0) //����
//    {
        *(uint16_t *)((uint32_t)g_ltdc_framebuf[0] + 2 * (800 * (480 - x - 1) + y)) = color;
//    }
//    else //����
//    {
//        *(uint16_t *)((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * y + x)) = color;
//    }

}

void ltdc_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{
    uint32_t psx;
    uint32_t psy;
    uint32_t pex;
    uint32_t pey;
    uint32_t timeout = 0;
    uint16_t offline;
    uint32_t addr;
    
//    if (lcdltdc.dir == 0)
//    {
        if (ex >= 480)
        {
            ex = 480 - 1;
        }
        
        if (sx >= 480)
        {
            sx = 480 - 1;
        }
        
        psx = sy;
        psy = 480 - ex - 1;
        pex = ey;
        pey = 480 - sx - 1;
//    }
//    else
//    {
//        psx = sx;
//        psy = sy;
//        pex = ex;
//        pey = ey;
//    }
    
//    offline = lcdltdc.pwidth - (pex - psx + 1);
//    addr = ((uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (800 * psy + psx));
//    offline = 800 - (pex - psx + 1);
//    addr = ((uint32_t)g_ltdc_framebuf[0] + 2 * (800 * psy + psx));
//    
//    /* ����DMA2D */
//    DMA2D->CR &= ~(DMA2D_CR_START);
//    DMA2D->CR = DMA2D_R2M;
//    DMA2D->OPFCCR = LTDC_PIXEL_FORMAT_RGB565;
//    DMA2D->OOR = offline;
//    DMA2D->OMAR = addr;
//    DMA2D->NLR = (pey - psy + 1) | ((pex - psx + 1) << 16);
//    DMA2D->OCOLR = color;
//    
//    /* ����DMA2D */
//    DMA2D->CR |= DMA2D_CR_START;
//    
//    /* �ȴ�DMA2D������� */
//    while ((DMA2D->ISR & (DMA2D_FLAG_TC)) == 0)
//    {
//        if (++timeout > 0x1FFFFF)
//        {
//            break;
//        }
//    } 
//    
//    /* ���DMA2D������ɱ�־ */
//    DMA2D->IFCR |= DMA2D_FLAG_TC;
}

void ltdc_clear(uint32_t color)
{
//    ltdc_fill(0, 0, 800 - 1, 480 - 1, color);
}

/* USER CODE END 1 */
