/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "oled.h"
#include "ds18b20.h"
#include "warning.h"
#include "addheat.h"
#include "bmp280.h"
#include "motorexecution.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
BMP280_HandleTypedef bmp280;
float pressure, temperature, humidity;
uint16_t sizeValue;
uint8_t dataValue[256];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t x = 0;
	uint8_t y = 0;
	float temperatureValue = 0;
	float kelvinTemperatureValue = 0;
	uint8_t temperatureIntegerValue = 0;
	uint8_t temperatureDecimalValue = 0;
	uint8_t temperatureLowLimitValue = 20;//温度下限
	uint8_t temperatureHighLimitValue = 30;//温度上限
	float pressureValue = 0;
	float standardAtmosphericPressureValue = 101.325e3;
	float oxygenSolubilityValue = 0;
	uint8_t oxygenSolubilityIntegerValue = 0;
	uint8_t oxygenSolubilityDecimalValue_1 = 0;
	uint8_t oxygenSolubilityDecimalValue_2 = 0;
	uint8_t oxygenSolubilityLimitValue = 5;//溶解氧极限值
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	OLED_Clear();
	OLED_ShowChinese(x + 16 + 16 * 0, y + 2 * 0, 0);
	OLED_ShowChinese(x + 16 + 16 * 1, y + 2 * 0, 1);
	OLED_ShowChinese(x + 16 + 16 * 2, y + 2 * 0, 2);
	OLED_ShowChinese(x + 16 + 16 * 3, y + 2 * 0, 3);
	OLED_ShowChinese(x + 16 + 16 * 4, y + 2 * 0, 4);
	OLED_ShowChinese(x + 16 + 16 * 5, y + 2 * 0, 5);
	OLED_ShowChinese(x + 16 * 0, y + 2 * 1, 6);
	OLED_ShowChinese(x + 16 * 1, y + 2 * 1, 7);
	OLED_ShowChar(x + 16 * 2 + 8 * 0, y + 2 * 1, ':', 16);
	OLED_ShowChinese(x + 16 * 0, y + 2 * 2, 8);
	OLED_ShowChinese(x + 16 * 1, y + 2 * 2, 9);
	OLED_ShowChar(x + 16 * 2 + 8 * 0, y + 2 * 2, ':', 16);
	OLED_ShowChinese(x + 16 * 0, y + 2 * 3, 10);
	OLED_ShowChinese(x + 16 * 1, y + 2 * 3, 11);
	OLED_ShowChar(x + 16 * 2 + 8 * 0, y + 2 * 3, 'C', 16);
	OLED_ShowChar(x + 16 * 2 + 8 * 1, y + 2 * 3, 's', 16);
	OLED_ShowChar(x + 16 * 2 + 8 * 2, y + 2 * 3, ':', 16);
	
	bmp280_init_default_params(&bmp280.params);
	bmp280.addr = BMP280_I2C_ADDRESS_0;
	bmp280.i2c = &hi2c1;
	while (!bmp280_init(&bmp280, &bmp280.params)) {
		sizeValue = sprintf((char *)dataValue, "BMP280 initialization failed\n");
		HAL_UART_Transmit(&huart1, dataValue, sizeValue, 1000);
		HAL_Delay(2000);
	}
	bool bme280p = bmp280.id == BME280_CHIP_ID;
	sizeValue = sprintf((char *)dataValue, "BMP280: found %s\n", bme280p?"BME280":"BMP280");
	HAL_UART_Transmit(&huart1, dataValue, sizeValue, 1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		temperatureValue = DS18B20_GetTemperture();
		temperatureIntegerValue = (int)temperatureValue;
		temperatureDecimalValue = 10 * (temperatureValue - (int)temperatureValue);
		OLED_ShowNum(x + 16 * 2 + 8 * 1, y + 2 * 1, temperatureIntegerValue, 2, 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 3, y + 2 * 1, '.', 16);
		OLED_ShowNum(x + 16 * 2 + 8 * 4, y + 2 * 1, temperatureDecimalValue, 1, 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 5, y + 2 * 1, 'C', 16);
		
		if(temperatureValue<temperatureLowLimitValue)//温度低于20度，报警并加热
		{
			warning();
			addHeat();
		}
		else if(temperatureValue>temperatureHighLimitValue)//温度高于30度，报警
		{
			warning();
		}
		
		kelvinTemperatureValue = 237.15 + temperatureValue;
		
		while(!bmp280_read_float(&bmp280, &temperature, &pressure, &humidity))
		{
			sizeValue = sprintf((char *)dataValue, "Temperature/pressure reading failed!\n");
			HAL_UART_Transmit(&huart1, dataValue, sizeValue, 1000);
			HAL_Delay(2000);
		}
		sizeValue = sprintf((char *)dataValue,"Pressure: %.2f Pa, Temperature: %.2f C", pressure, temperature);
		HAL_UART_Transmit(&huart1, dataValue, sizeValue, 1000);
		if(bme280p)
		{
			sizeValue = sprintf((char *)dataValue,", Humidity: %.2f\n", humidity);
			HAL_UART_Transmit(&huart1, dataValue, sizeValue, 1000);
		}
		else
		{
			sizeValue = sprintf((char *)dataValue, "\n");
			HAL_UART_Transmit(&huart1, dataValue, sizeValue, 1000);
		}
		
		pressureValue = pressure;
		OLED_ShowNum(x + 16 * 2 + 8 * 1, y + 2 * 2, pressureValue/1000, 6, 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 7, y + 2 * 2, 'k', 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 8, y + 2 * 2, 'P', 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 9, y + 2 * 2, 'a', 16);
		
		oxygenSolubilityValue = (pressure / standardAtmosphericPressureValue) * (477.8 / (temperatureValue + 32.26));
		oxygenSolubilityIntegerValue = (int)oxygenSolubilityValue;
		oxygenSolubilityDecimalValue_1 = 10 * (oxygenSolubilityValue - (int)oxygenSolubilityValue);
		oxygenSolubilityDecimalValue_2 = 10 * (10 * (oxygenSolubilityValue - (int)oxygenSolubilityValue) - (int)(10 * (oxygenSolubilityValue - (int)oxygenSolubilityValue)));
		OLED_ShowNum(x + 16 * 2 + 8 * 1, y + 2 * 3, oxygenSolubilityIntegerValue, 2, 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 3, y + 2 * 3, '.', 16);
		OLED_ShowNum(x + 16 * 2 + 8 * 4, y + 2 * 3, oxygenSolubilityDecimalValue_1, 1, 16);
		OLED_ShowNum(x + 16 * 2 + 8 * 5, y + 2 * 3, oxygenSolubilityDecimalValue_2, 1, 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 6, y + 2 * 3, 'm', 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 7, y + 2 * 3, 'g', 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 8, y + 2 * 3, '/', 16);
		OLED_ShowChar(x + 16 * 2 + 8 * 9, y + 2 * 3, 'L', 16);
		
		if(oxygenSolubilityValue<oxygenSolubilityLimitValue)//溶解氧低于5mg/L，步进电机转动
		{
			MotorExecution();
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
