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
#include <mitsuba-driver-data-module.hpp>
#include <orion-data-module.hpp>
#include <proton1-data-module.hpp>
#include "main.h"
#include "cmsis_os.h"
#include "gps-driver.h"
#include "rf-driver/rf-message-helper.h"
#include "rf-driver/transport-layer.h"
#include "bno055.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart1;
osThreadId GPS_RequestHandle;
osThreadId MC_RequestHandle;
osThreadId CAN_RequestHandle;
osThreadId RF_RequestHandle;
osThreadId CAN_SendHandle;
osThreadId IMU_RequestHandle;
osMutexId RF_FIFOHandle;
PROTON1_MESSAGE_0 mppt0(subsystem_info::MPPT0_MSG_ID);
//PROTON1_MESSAGE_0 mppt1(subsystem_info::MPPT1_MSG_ID);
//PROTON1_MESSAGE_0 mppt2(subsystem_info::MPPT2_MSG_ID);
ORION_MESSAGE_0 bms0(subsystem_info::BMS0_MSG_ID);
MITSUBA_DRIVER_TX_RL_MESSAGE mcRequest(subsystem_info::MOTORTX_RL_MSG_ID);
MITSUBA_DRIVER_RX_FRAME_0 motorRx0(subsystem_info::MOTORRX0_RL_MSG_ID);
MITSUBA_DRIVER_RX_FRAME_2 motorRx2(subsystem_info::MOTORRX2_RL_MSG_ID);
// Setup RF module
RF_PACKET msg0{huart2.Instance};

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
void Start_MC_Request(void const * argument);
void Start_GPS_Request(void const * argument);
void Start_IMU_Request(void const * argument);
void Start_CAN_Request(void const * argument);
void Start_CAN_Send(void const * argument);
void Start_RF_Request(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//Testing Defines
#define GPS_TEST
#define IMU_TEST
#define CAN_TEST
#define CAN_REQUEST
#define CAN_SEND
#define CAN_RF_TEST
#include <string.h>
#include <stdio.h>
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
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */

  /* Create the mutex(es) */
  /* definition and creation of RF_FIFO */
  osMutexDef(RF_FIFO);
  RF_FIFOHandle = osMutexCreate(osMutex(RF_FIFO));

  PROTON1_MESSAGE_0 mppt0(subsystem_info::MPPT0_MSG_ID);
  mppt0.SetupReceive(nullptr);
//  PROTON1_MESSAGE_0 mppt1(subsystem_info::MPPT1_MSG_ID);
//  mppt1.SetupReceive(nullptr);
//  PROTON1_MESSAGE_0 mppt2(subsystem_info::MPPT2_MSG_ID);
//  mppt2.SetupReceive(nullptr);

  ORION_MESSAGE_0 bms0(subsystem_info::BMS0_MSG_ID);
  bms0.SetupReceive(nullptr);

  // Motor Controller
  // request message
  MITSUBA_DRIVER_TX_RL_MESSAGE mcRequest(subsystem_info::MOTORTX_RL_MSG_ID);
  // first return message
  MITSUBA_DRIVER_RX_FRAME_0 motorRx0(subsystem_info::MOTORRX0_RL_MSG_ID);
  motorRx0.SetupReceive(nullptr);
  // second return message
  MITSUBA_DRIVER_RX_FRAME_2 motorRx2(subsystem_info::MOTORRX2_RL_MSG_ID);
  motorRx2.SetupReceive(nullptr);

  // Start the CAN peripheral
  SUBSYSTEM_DATA_MODULE::StartCAN();
  Start_CAN_Request(); // Send the first request packets for data from CAN

///***************************GPS TEST***********************/
#ifdef GPS_TEST
  osThreadDef(GPS_Request, Start_GPS_Request, osPriorityNormal, 0, 128);
  GPS_RequestHandle = osThreadCreate(osThread(GPS_Request), NULL);
#endif
///***************************CAN RF TEST********************/
#ifdef CAN_RF_TEST
  osThreadDef(RF_Request, Start_RF_Request, osPriorityNormal, 0, 128);
  RF_RequestHandle = osThreadCreate(osThread(RF_Request), NULL);
#endif
///***************************IMU TEST***********************/
#ifdef IMU_TEST
  osThreadDef(IMU_Request, Start_IMU_Request, osPriorityNormal, 0, 128);
  IMU_RequestHandle = osThreadCreate(osThread(IMU_Request), NULL);
#endif
///***************************CAN TEST***********************/
#ifdef CAN_TEST
  osThreadDef(CAN_Send, Start_CAN_Send, osPriorityNormal, 0, 128);
  CAN_SendHandle = osThreadCreate(osThread(CAN_Send), NULL);
#endif
///***************************CAN REQUEST********************/
#ifdef CAN_REQUEST
  osThreadDef(CAN_Request, Start_CAN_Request, osPriorityNormal, 0, 128);
  CAN_RequestHandle = osThreadCreate(osThread(CAN_Request), NULL);
#endif

  /* Start scheduler */
  osKernelStart();
  //Infinite Loop
  while(1);
  /* USER CODE END 3 */
}



#ifdef GPS_TEST
  void Start_GPS_Request(void const * argument)
  {
	  GPS_init(huart1.Instance);
	  GPS_startReception();
	  /* Infinite loop */
	  for(;;)
	  {
		  if(GPS_isDataAvailable())
		  {
			  GPS_Data_t data = GPS_getLatestData();
			  GPS_TO_RF::AddMessage(&msg0,333, &data); //TODO!! missing rf_id
		  }
		  osDelay(1);
	  }
  }
#endif

#ifdef CAN_RF_TEST
  void Start_RF_Request(void const * argument)
  {
	  /* Infinite loop */
	  for(;;)
	  {
		  // check to see if we have gotten any messages
		  if(!motorRx0.isFifoEmpty())
		  {
			  bool receivedSomething;
			  MITSUBA_DRIVER_RX_FRAME_0_DATA_PACKET motorPacket = motorRx0.GetOldestDataPacket(&receivedSomething);
			  if(receivedSomething)
			  {
				  //Nice
				  float l = motorPacket.motorRPM;
				  CAN_TO_RF::AddMessage(&msg0, RF_TYPES::MITSUBA_FRAME0, subsystem_rf_ids::MITSUBARX0_RL, &motorPacket);
			  }
		  }
		  if(!motorRx2.isFifoEmpty())
		  {
			  bool receivedSomething;
			  MITSUBA_DRIVER_RX_FRAME_2_DATA_PACKET motorPacket = motorRx2.GetOldestDataPacket(&receivedSomething);
			  if(receivedSomething)
			  {
				  //Nice
				  float l = motorPacket.accelPosError;
				  CAN_TO_RF::AddMessage(&msg0, RF_TYPES::MITSUBA_FRAME2, subsystem_rf_ids::MITSUBARX2_RL, &motorPacket);
			  }
		  }
		  if(!mppt0.isFifoEmpty())
		  {
			  bool receivedSomething;
			  PROTON1_MESSAGE_0_DATA_PACKET mpptPacket = mppt0.GetOldestDataPacket(&receivedSomething);
			  if(receivedSomething)
			  {
				  //Nice
				  float vin = mpptPacket.arrayVoltage;
				  CAN_TO_RF::AddMessage(&msg0, RF_TYPES::PROTON1, subsystem_rf_ids::MPPT0, &mpptPacket);
			  }
		  }
		  if(!bms0.isFifoEmpty())
		  {
			  bool receivedSomething;
			  ORION_MESSAGE_0_DATA_PACKET bmsPacket = bms0.GetOldestDataPacket(&receivedSomething);
			  if(receivedSomething)
			  {
				  //Nice
				  float voltH = bmsPacket.highCellVoltage;
				  CAN_TO_RF::AddMessage(&msg0, RF_TYPES::ORION, subsystem_rf_ids::ORION0, &bmsPacket);
			  }
		  }
		  osDelay(1);
	  }
  }
#endif

#ifdef IMU_TEST
  void Start_IMU_Request(void const * argument)
  {
	  bno055Init();
	  /* Infinite loop */
	  for(;;)
	  {
		  IMU_DATA_t imuData = bno055GetPacket();
		  IMU_TO_RF::AddMessage(&msg0, 123, &imuData); //TODO!! RF_ID!!
		  osDelay(1);
	  }
  }
#endif

#ifdef CAN_REQUEST
void Start_CAN_Request(void const * argument){
    /* Infinite loop */
    for(;;)
    {
    	// request data from the motor controller
    	mcRequest.txData = { 1, 1, 1 }; // Do we request even if data not processed?
		mcRequest.SendData();
		mppt0.SendData();
	    osDelay(1);
    }
}
#endif

#ifdef CAN_TEST
void Start_CAN_Send(void const * argument){
    /* Infinite loop */
    for(;;)
    {
    	if(!msg0.isPacketEmpty()){
    		msg0.Send();
    	}
    	osDelay(1);
    }
}
#endif

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
//  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 57600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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