/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
#include "stm32g4xx_nucleo.h"
#include <stdio.h>

#include "stm32g4xx_ll_dma.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_crs.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_spi.h"
#include "stm32g4xx_ll_tim.h"
#include "stm32g4xx_ll_gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RCC_OSC32_IN_Pin LL_GPIO_PIN_14
#define RCC_OSC32_IN_GPIO_Port GPIOC
#define RCC_OSC32_OUT_Pin LL_GPIO_PIN_15
#define RCC_OSC32_OUT_GPIO_Port GPIOC
#define RCC_OSC_IN_Pin LL_GPIO_PIN_0
#define RCC_OSC_IN_GPIO_Port GPIOF
#define RCC_OSC_OUT_Pin LL_GPIO_PIN_1
#define RCC_OSC_OUT_GPIO_Port GPIOF
#define VL530LX_IT_Pin LL_GPIO_PIN_3
#define VL530LX_IT_GPIO_Port GPIOC
#define VL530LX_IT_EXTI_IRQn EXTI3_IRQn
#define PWM_CH1_Pin LL_GPIO_PIN_0
#define PWM_CH1_GPIO_Port GPIOA
#define PWM_CH2_Pin LL_GPIO_PIN_1
#define PWM_CH2_GPIO_Port GPIOA
#define SPI_NSS_Pin LL_GPIO_PIN_4
#define SPI_NSS_GPIO_Port GPIOA
#define PWM_DMA_Pin LL_GPIO_PIN_6
#define PWM_DMA_GPIO_Port GPIOA
#define IN_4_Pin LL_GPIO_PIN_11
#define IN_4_GPIO_Port GPIOB
#define IN_3_Pin LL_GPIO_PIN_12
#define IN_3_GPIO_Port GPIOB
#define IN_2_Pin LL_GPIO_PIN_11
#define IN_2_GPIO_Port GPIOA
#define IN_1_Pin LL_GPIO_PIN_12
#define IN_1_GPIO_Port GPIOA
#define T_SWDIO_Pin LL_GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin LL_GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define LORA_IT_RX_Pin LL_GPIO_PIN_2
#define LORA_IT_RX_GPIO_Port GPIOD
#define LORA_IT_RX_EXTI_IRQn EXTI2_IRQn
#define T_SWO_Pin LL_GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
