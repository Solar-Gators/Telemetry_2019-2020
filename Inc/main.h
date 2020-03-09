/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

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
#define TFT_D_C_Pin GPIO_PIN_5
#define TFT_D_C_Pin_Num 5
#define TFT_D_C_GPIO_Port GPIOA
#define SPI2_NSS_Pin GPIO_PIN_1
#define SPI2_NSS_Pin_Num 1
#define SPI2_NSS_GPIO_Port GPIOB
#define TFT_RST_Pin GPIO_PIN_4
#define TFT_RST_Pin_Num 4
#define TFT_RST_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ENC_B_Pin GPIO_PIN_15
#define ENC_B_GPIO_Port GPIOA
#define ENC_A_Pin GPIO_PIN_10
#define ENC_A_GPIO_Port GPIOC
#define ENC_OK_Pin GPIO_PIN_11
#define ENC_OK_GPIO_Port GPIOC
#define ENC_OK_EXTI_IRQn EXTI4_15_IRQn
#define BTN_CANCEL_Port GPIOC
#define BTN_CANCEL_Pin GPIO_PIN_12
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
