/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define BTN_J1_Pin GPIO_PIN_1
#define BTN_J1_GPIO_Port GPIOC
#define BTN_J1_EXTI_IRQn EXTI1_IRQn
#define BTN_INICIO_Pin GPIO_PIN_2
#define BTN_INICIO_GPIO_Port GPIOC
#define BTN_J2_Pin GPIO_PIN_3
#define BTN_J2_GPIO_Port GPIOC
#define BTN_J2_EXTI_IRQn EXTI3_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define J2_LED2_Pin GPIO_PIN_4
#define J2_LED2_GPIO_Port GPIOC
#define Seg_C_Pin GPIO_PIN_5
#define Seg_C_GPIO_Port GPIOC
#define J1_LED2_Pin GPIO_PIN_1
#define J1_LED2_GPIO_Port GPIOB
#define J1_LED1_Pin GPIO_PIN_2
#define J1_LED1_GPIO_Port GPIOB
#define Seg_F_Pin GPIO_PIN_12
#define Seg_F_GPIO_Port GPIOB
#define J2_LED1_Pin GPIO_PIN_13
#define J2_LED1_GPIO_Port GPIOB
#define J1_LED4_Pin GPIO_PIN_14
#define J1_LED4_GPIO_Port GPIOB
#define J1_LED3_Pin GPIO_PIN_15
#define J1_LED3_GPIO_Port GPIOB
#define Seg_B_Pin GPIO_PIN_6
#define Seg_B_GPIO_Port GPIOC
#define Seg_G_Pin GPIO_PIN_7
#define Seg_G_GPIO_Port GPIOC
#define Seg_A_Pin GPIO_PIN_8
#define Seg_A_GPIO_Port GPIOC
#define Seg_E_Pin GPIO_PIN_11
#define Seg_E_GPIO_Port GPIOA
#define Seg_D_Pin GPIO_PIN_12
#define Seg_D_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define J2_LED3_Pin GPIO_PIN_8
#define J2_LED3_GPIO_Port GPIOB
#define J2_LED4_Pin GPIO_PIN_9
#define J2_LED4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
