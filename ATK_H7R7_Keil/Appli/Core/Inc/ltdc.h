/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.h
  * @brief   This file contains all the function prototypes for
  *          the ltdc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LTDC_H__
#define __LTDC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern LTDC_HandleTypeDef hltdc;

/* USER CODE BEGIN Private defines */
/* LTDC LCD���Ų��� */
#define LTDC_BL_GPIO_PORT               GPIOD
#define LTDC_BL_GPIO_PIN                GPIO_PIN_15
#define LTDC_BL_GPIO_CLK_ENABLE()       do { __HAL_RCC_GPIOD_CLK_ENABLE(); } while (0)

#define LTDC_BL(x)                      do { (x) ?                                                                  \
                                            HAL_GPIO_WritePin(LTDC_BL_GPIO_PORT, LTDC_BL_GPIO_PIN, GPIO_PIN_SET):   \
                                            HAL_GPIO_WritePin(LTDC_BL_GPIO_PORT, LTDC_BL_GPIO_PIN, GPIO_PIN_RESET); \
                                        } while (0)
/* USER CODE END Private defines */

void MX_LTDC_Init(void);

/* USER CODE BEGIN Prototypes */
void BL_Init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __LTDC_H__ */

