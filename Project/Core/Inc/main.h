/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define Buzzer_VCC_Pin GPIO_PIN_4
#define Buzzer_VCC_GPIO_Port GPIOA
#define Buzzer_GND_Pin GPIO_PIN_5
#define Buzzer_GND_GPIO_Port GPIOA
#define SM_IN1_Pin GPIO_PIN_12
#define SM_IN1_GPIO_Port GPIOB
#define SM_IN2_Pin GPIO_PIN_13
#define SM_IN2_GPIO_Port GPIOB
#define SM_IN3_Pin GPIO_PIN_14
#define SM_IN3_GPIO_Port GPIOB
#define SM_IN4_Pin GPIO_PIN_15
#define SM_IN4_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOB
#define HeatingPlate_Pin GPIO_PIN_4
#define HeatingPlate_GPIO_Port GPIOB
#define DS18B20_Pin GPIO_PIN_8
#define DS18B20_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_9
#define Buzzer_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
