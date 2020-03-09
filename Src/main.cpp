/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "hspi.h"
#include "gfx.h"
#include "text-box.h"
#include "quarter-sorter-specific.h"
#include "selection-encoder.h"
#include <stdio.h>
#include "sw-debounce.h"
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
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

SELECTION_ENCODER* encoderPtr = nullptr;

SW_DEBOUNCE* okButtonPtr = nullptr;
SW_DEBOUNCE* cancelButtonPtr = nullptr;

/* USER CODE BEGIN PV */
const uint16_t backgroundColor = ILI9341_BLACK;
const uint16_t fontColor = ILI9341_DARK_ORANGE;
const uint16_t lineColor = ILI9341_DARK_ORANGE;
const uint16_t fontColorGood = 0x3781;
const uint16_t fontColorHigh = ILI9341_RED;
const uint16_t fontColorLow = ILI9341_CYAN;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM6_Init(void);

void IntToString(char * buff, int input, int base = 10);

static double PRECISION = 0.01;
char * dtoa(char *s, double n);

void updateIntSelector(TFT_TEXT_BOX &selector, int value);
void updateFloatSelector(TFT_TEXT_BOX &selector, float value, int precision, int minValue = -1000, int maxValue = -1000, int backgroundColor = -1);

#define MIN_BAT_VOLTAGE 78
#define MIN_TEMP		0
#define MIN_BAT_CURRENT 0
#define MAX_BAT_VOLTAGE 109
#define MAX_TEMP		0
#define MAX_BAT_CURRENT 0

//void updateSpeed(TFT_TEXT_BOX &speedSelector, int value);
//void updateVoltage();
//void updateCurrent();
//void updateTemperature();


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
	MX_SPI2_Init();
	MX_TIM6_Init();

	/* USER CODE BEGIN 2 */
	TFT_GFX tftDisplay{hspi2.Instance};

	//Size of the box section titles
	/**
	 * SPEED
	 * LOW CELL VOLTAGE
	 * HIGH CELL VOLTAGE
	 * CURRENT
	 * AVG. TEMPERATURE
	 */
	const uint16_t textSize = 1;
	const uint16_t lineThickness = 5;
	const uint8_t chosenStatesFontSize = 2;
	const uint8_t stateSelectorFontSize = 3;

	//LANDSCAPE W/ SD CARD SLOT ON LEFT SIDE
	tftDisplay.setRotation(1);

	//Set background to correct color and add outline
	GUI_API::drawSelectionLines(tftDisplay, backgroundColor, fontColor, lineColor, lineThickness);


	//CREATING SPEED TEXT BOX (TOP LEFT SQUARE)
	TFT_TEXT_BOX bottomSpeedTxtSel{&tftDisplay,backgroundColor,lineThickness + 0.15 * tftDisplay.width(), tftDisplay.height()/2 - (2*lineThickness), (int16_t)(tftDisplay.width() - lineThickness - 8), false};
	uint16_t bottomSpeedTxt = bottomSpeedTxtSel.write("SPEED (mph)", fontColor, 1);

	//CELL VOLTAGE TEXT BOX (TOP RIGHT)
	TFT_TEXT_BOX bottomVoltTxtSel{&tftDisplay,backgroundColor,lineThickness + 0.6 * tftDisplay.width(), tftDisplay.height()/2 - (2*lineThickness), (int16_t)(tftDisplay.width() - lineThickness - 8), false};
	uint16_t bottomVoltTxt = bottomVoltTxtSel.write("BATTERY VOLTAGE", fontColor, 1);

	//BATTERY CURRENT TEXT BOX (BOTTOM LEFT)
	TFT_TEXT_BOX bottomCurrentTxtSel{&tftDisplay,backgroundColor,lineThickness + 0.1 * tftDisplay.width(), tftDisplay.height() - (3*lineThickness), (int16_t)(tftDisplay.width() - lineThickness - 8), false};
	uint16_t bottomCurrentTxt = bottomCurrentTxtSel.write("BATTERY CURRENT", fontColor, 1);

	//AVG. TEMPERATURE TEXT BOX (BOTTOM RIGHT)
	TFT_TEXT_BOX bottomTempTxtSel{&tftDisplay,backgroundColor,lineThickness + 0.6 * tftDisplay.width(), tftDisplay.height() - (3*lineThickness), (int16_t)(tftDisplay.width() - lineThickness - 8), false};
	uint16_t bottomTempTxt = bottomTempTxtSel.write("TEMPERATURE (F)", fontColor, 1);


	//SPEED SELECTOR
	TFT_TEXT_BOX selectorSpeed{&tftDisplay,backgroundColor, lineThickness + 0.0 * tftDisplay.width(), 0.2 * tftDisplay.height() - (lineThickness), (int16_t)(tftDisplay.width() / 2), true};
	uint16_t speedTxt = selectorSpeed.write("", fontColor, 6);

	//BATTERY CURRENT SELECTOR
	TFT_TEXT_BOX selectorBatCurrent{&tftDisplay,backgroundColor, lineThickness + 0.0 * tftDisplay.width(), 0.70 * tftDisplay.height() - (lineThickness), (int16_t)(tftDisplay.width() / 2), true};
	uint16_t batCurrentTxt = selectorBatCurrent.write("", fontColor, 6);

	//BATTERY VOLTAGE SELECTOR
	TFT_TEXT_BOX selectorBatVolt{&tftDisplay,backgroundColor, lineThickness + 0.50 * tftDisplay.width(), 0.2 * tftDisplay.height() - (lineThickness), (int16_t)(tftDisplay.width() - lineThickness), true};
	uint16_t batVoltTxt = selectorBatVolt.write("", fontColor, 6);

	//TEMPERATURE SELECTOR
	TFT_TEXT_BOX selectorTemp{&tftDisplay,backgroundColor, lineThickness + 0.50 * tftDisplay.width(), 0.70 * tftDisplay.height() - (lineThickness), (int16_t)(tftDisplay.width() - lineThickness), true};
	uint16_t tempTxt = selectorTemp.write("", fontColor, 6);



	/**
	 * TODO
	 * 1. EXTRAPOLATE INT TO STRING INTO A FUNCTION SO THAT THE DIFF. PARTS CAN USE IT
	 * 		78 < batter voltage < 109
	 * 2. CREATE SELECTORS FOR EACH QUADRANT
	 * 3. IMPLEMENT COLOR FONT CHANGE FOR TOO HIGH/TOO LOW
	 */

	int prev_s = 0;
	int prev_t = 0;
	while(true){

		int i;


		int s = rand() % 2;
		//		int s = 20;

		//		if(s != prev_s)
		//		{
		//			updateFloatSelector(selectorSpeed, s, 3);
		//			int prev_s = s;
		//		}

		if(s != prev_s)
		{
			updateFloatSelector(selectorSpeed, 20, 3);
			int prev_s = s;
		}


		int t = rand() % 110;
		updateFloatSelector(selectorTemp, t, 3);

		float q = (float)rand()/(RAND_MAX + 1)+1+(rand()%150);
		float r = (float)rand()/(RAND_MAX + 1)+1+(rand()%150);
		updateFloatSelector(selectorBatVolt, q, 3, MIN_BAT_VOLTAGE, MAX_BAT_VOLTAGE);
		updateFloatSelector(selectorBatCurrent, r, 3);


		// 20ms ~ 50Hz
		//HAL_Delay(20);

	}

}

/**
 * @brief Change an int to char buffer
 */
void IntToString(char * buff, int input, int base)
{
	itoa(input, buff, base);
	return;
	//	return buf;
}

char * dtoa(char *s, double n) {
	// handle special cases
	if (isnan(n)) {
		strcpy(s, "nan");
	} else if (isinf(n)) {
		strcpy(s, "inf");
	} else if (n == 0.0) {
		strcpy(s, "0");
	} else {
		int digit, m, m1;
		char *c = s;
		int neg = (n < 0);
		if (neg)
			n = -n;
		// calculate magnitude
		m = log10(n);
		int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp) {
			if (m < 0)
				m -= 1.0;
			n = n / pow(10.0, m);
			m1 = m;
			m = 0;
		}
		if (m < 1.0) {
			m = 0;
		}
		// convert the number
		while (n > PRECISION || m >= 0) {
			double weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0)
				*(c++) = '.';
			m--;
		}
		if (useExp) {
			// convert the exponent
			int i, j;
			*(c++) = 'e';
			if (m1 > 0) {
				*(c++) = '+';
			} else {
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0) {
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			for (i = 0, j = m-1; i<j; i++, j--) {
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
			}
			c += m;
		}
		*(c) = '\0';
	}
	return s;
}

void updateIntSelector(TFT_TEXT_BOX &selector, int value)
{
	char buffer[10];
	IntToString(buffer, value);


	if(value > 30 && value < 70)
		selector.write(buffer, fontColor, 6);
	else if(value < 30)
		selector.write(buffer, fontColorLow, 6);
	else
		selector.write(buffer, fontColorHigh, 6);


	return;
}

void updateFloatSelector(TFT_TEXT_BOX &selector, float value, int precision, int minValue, int maxValue, int backgroundColor)
{
	char buffer[precision + 2];
	dtoa(buffer, value);

	if(backgroundColor != -1)
	{
		selector.write(buffer, backgroundColor, 4);
	}


	else if(minValue == -1000 && maxValue == -1000)
	{
		selector.write(buffer, fontColor, 4);
	}

	else
	{
		if(value >= maxValue)
			selector.write(buffer, fontColorHigh, 4);
		else if(value <= minValue)
			selector.write(buffer, fontColorLow, 4);
		else
			selector.write(buffer, fontColorGood, 4);

	}

	return;
}

/**
 * Might not need these but keep them here anyways in case i decide to implement them
 */
//void updateSpeed()
//{
//	return;
//}
//void updateVoltage()
//{
//	return;
//}
//void updateCurrent()
//{
//	return;
//}
//void updateTemperature()
//{
//	return;
//}


/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void)
{

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 7;
	hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
	if (HAL_SPI_Init(&hspi2) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */
	//Send 1 random byte to reset the sck
	uint8_t temp = 0;
	HAL_SPI_Transmit(&hspi2, &temp, sizeof(temp), HAL_MAX_DELAY);
	resetTftBoard();
	pullCSLow();
	ili9341_hspi_init(hspi2.Instance);
	/* USER CODE END SPI2_Init 2 */

}

/**
 * @brief TIM6 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM6_Init(void)
{

	/* USER CODE BEGIN TIM6_Init 0 */

	/* USER CODE END TIM6_Init 0 */

	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* USER CODE BEGIN TIM6_Init 1 */
	//Set a period of 2ms
	/* USER CODE END TIM6_Init 1 */
	htim6.Instance = TIM6;
	htim6.Init.Prescaler = 240-1;
	htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim6.Init.Period = 400-1;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN TIM6_Init 2 */
	//Clear status reg
	htim6.Instance->SR &= TIM_SR_UIF;
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 3, 0);
	/* USER CODE END TIM6_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(TFT_D_C_GPIO_Port, TFT_D_C_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : SPI2_NSS_Pin */
	GPIO_InitStruct.Pin = SPI2_NSS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(SPI2_NSS_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : TFT_D_C_Pin*/
	GPIO_InitStruct.Pin = TFT_D_C_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(TFT_D_C_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : TFT_RST_Pin */
	GPIO_InitStruct.Pin = TFT_RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(TFT_RST_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : ENC_B_Pin */
	GPIO_InitStruct.Pin = ENC_B_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(ENC_B_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : ENC_A_Pin */
	GPIO_InitStruct.Pin = ENC_A_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(ENC_A_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : ENC_OK_Pin */
	GPIO_InitStruct.Pin = ENC_OK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(ENC_OK_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : BTN_CANCEL_Pin */
	GPIO_InitStruct.Pin = BTN_CANCEL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(BTN_CANCEL_Port, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 1, 0);
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
void assert_failed(char *file, uint32_t line)
{ 
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
