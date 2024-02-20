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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
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
char message[]="hello world";
	uint8_t res[2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	  HAL_UART_Transmit_IT(&huart1, res, 2);
//	  HAL_UART_Receive_IT(&huart1, res, 2);
//}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t a,d,c,b;
	uint16_t encoder_value, encoder_va;
	uint8_t coder;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
// char a,b,c,d;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init(); //串口初始化
  MX_TIM2_Init();  //定时器初始化
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, res, 2);

  HAL_UART_Transmit_IT(&huart1, "hh", 2);  // key1闈犺繎涓嬭浇锟????   key2闈犺繎锟????
  a = (HAL_GPIO_ReadPin(GPIOD, key1_8_Pin));   //PD2          //pb6
  b = (HAL_GPIO_ReadPin(GPIOB, key1_4_Pin));   //PB3          //pb7
  c = (HAL_GPIO_ReadPin(GPIOB, key1_2_Pin));   //PB4          //pb8
  d = (HAL_GPIO_ReadPin(GPIOB, key1_1_Pin));   //PB5          //pb9

//  HAL_UART_Transmit_IT(&huart1, a,1);
//  HAL_Delay(50);
//  HAL_UART_Transmit_IT(&huart1, b,1);
//  HAL_Delay(50);
//  HAL_UART_Transmit_IT(&huart1, c,1);
//  HAL_Delay(50);
//  HAL_UART_Transmit_IT(&huart1, d,1);
//  HAL_Delay(50);
//  HAL_UART_Transmit_IT(&huart1, 'E',1);
  HAL_Delay(500);
  // 6 7 8 9  ~  8 4 2 1
  encoder_value = ((HAL_GPIO_ReadPin(GPIOB, key2_8_Pin)) << 3) |
          ((HAL_GPIO_ReadPin(GPIOB, key2_4_Pin)) << 2) |
          ((HAL_GPIO_ReadPin(GPIOB, key2_2_Pin)) << 1) |
          (HAL_GPIO_ReadPin(GPIOB, key2_1_Pin));
//  HAL_UART_Transmit_IT(&huart1, encoder_value,1);
  encoder_va = ((HAL_GPIO_ReadPin(GPIOD, key1_8_Pin)) << 3) |
          ((HAL_GPIO_ReadPin(GPIOB, key1_4_Pin)) << 2) |
          ((HAL_GPIO_ReadPin(GPIOB, key1_2_Pin)) << 1) |
          (HAL_GPIO_ReadPin(GPIOB, key1_1_Pin));
//  HAL_UART_Transmit_IT(&huart1, !encoder_va,1);
//  HAL_Delay(1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//	  HAL_UART_Transmit_IT(&huart1, encoder_va,1);
//	  HAL_Delay(1000);
	  modbus_service();  // modbus服务
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
