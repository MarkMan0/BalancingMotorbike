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
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "stm32f3xx_ll_usart.h"
#include "callbacks.h"
#include "MPU6050.h"
#include "orientation.h"
#include "MovementController.h"
#include "CurrContParams.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define USART_RX_BUFLEN 	(10)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

void usart_rx(uint8_t);
void initADC();
void initDMA(uint32_t toAddr, uint32_t sz);
void initTIM1();

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
  

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM7_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */

  initDMA((uint32_t) (CCParams.adcBuff), 2);


  //register USART callbacks and enable interrupts
  USART2_register_RXNE_callback(usart_rx);
  //LL_USART_EnableIT_RXNE(USART2);

  USART1_register_RXNE_callback(usart_rx);
  //LL_USART_EnableIT_RXNE(USART1);



  initADC();
  initServo();
  initRearMotor();
  initTIM1();

  LL_TIM_EnableIT_UPDATE(TIM6);
  LL_TIM_EnableCounter(TIM6);

  LL_TIM_EnableIT_UPDATE(TIM7);
  LL_TIM_EnableCounter(TIM7);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  MPU6050 mpu = { 0 };	//initialize to 0, rest is done in init
  //MPU6050init(&mpu);
  orientation.mpu = &mpu;

  while (1)
  {

	  //readForRoll(&mpu);
	  //calcRoll(&o);

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
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2, LL_RCC_PLL_MUL_8);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {
    
  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  
  }
  LL_Init1msTick(32000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(32000000);
  LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK1);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
  LL_RCC_SetTIMClockSource(LL_RCC_TIM1_CLKSOURCE_PLL);
  LL_RCC_SetADCClockSource(LL_RCC_ADC12_CLKSRC_PLL_DIV_1);
}

/* USER CODE BEGIN 4 */

void usart_rx(uint8_t x) {
	static uint8_t buffer[USART_RX_BUFLEN];
	static uint8_t ind = 0;
	if(ind < USART_RX_BUFLEN) {
		buffer[ind++] = x;
	} else {
		ind = 0;
	}
	if(x == '\n' || x == '\r'  || x == '\0') {
		//end of command
		MC_handleCommand((MovementControl*) &MC, buffer);
		ind = 0;
	}
	return;
}

void initADC() {

	LL_ADC_EnableInternalRegulator(ADC1);
	LL_mDelay(1);	//wait at least 10us for regulator

	while(!LL_ADC_IsInternalRegulatorEnabled(ADC1)) {}	//ensure regulator is on
	while(LL_ADC_IsEnabled(ADC1)) {}	//if enabled, halt
	LL_ADC_StartCalibration(ADC1, LL_ADC_SINGLE_ENDED);
	while(LL_ADC_IsCalibrationOnGoing(ADC1)) {} //wait for end of calibration
	LL_mDelay(10);

	LL_ADC_EnableIT_EOC(ADC1); //enable interrupt

	LL_ADC_Enable(ADC1);

	while(!LL_ADC_IsActiveFlag_ADRDY(ADC1)) {}	//wait for ADC ready

	LL_ADC_REG_StartConversion(ADC1);	//enable conversions
	LL_TIM_EnableCounter(TIM6);			//start timer
}

void initDMA(uint32_t addr, uint32_t sz) {

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	  LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_1, addr);

	  LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA));
	  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
	  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
	  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);
	  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
	  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, sz);
	  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
}

void initTIM1() {
	  LL_TIM_ClearFlag_UPDATE(TIM1);	//set by init function
	  LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);	//enable PWM channels
	  LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH4);
	  LL_TIM_EnableAllOutputs(TIM1);		//enable outputs
	  LL_TIM_GenerateEvent_UPDATE(TIM1);	//generate an update event to sych adc to first address in dma
	  LL_TIM_EnableCounter(TIM1);
}

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
