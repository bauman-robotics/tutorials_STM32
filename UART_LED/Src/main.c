/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"
#include "String.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint8_t buf_uplevel[11];
extern uint8_t gotAll;
extern uint8_t time_is_over;

int commandNumber( uint8_t*);
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
//extern int A;

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  USART1->CR1 |= USART_CR1_RXNEIE;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  
		uint8_t comp1[5] = "LEDOn";	// template LED on
		uint8_t comp2[5] = "LEDBl";	// template LED blinkig
		uint8_t comp3[5] = "LEDOf"; // template LED off
		int flag = 0;

//////////////////////////////////////////////////////////////////////////
//			//comparation ver 1.0
			
//						for ( int i = 0; i < sizeof(comp); i++){
//				if((( unsigned char*)( &buf_uplevel))[i] != comp[i]){
//					flag = 0;
//				}	
//			
//			}
//			if( flag == 1){  //LED blinking		
//				if (time_is_over) {
//					time_is_over = 0;
//					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
//				}
//			}
//			else {
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);  // Led_off
//				}
//			}
//		else {
//				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);  // Led_off
//				}
////////////////////////////////////////////////////////////////////////////
			
			if (gotAll){
				flag = 0;
	//		strcmp(buf_uplevel, comp1);
	//		if ( commandNumber( comp1) == 1)
				if( (comp1[3] == buf_uplevel[3]) && (comp1[4] == buf_uplevel[4]))
					flag = 1;
				else if(  (comp2[3] == buf_uplevel[3]) && (comp2[4] == buf_uplevel[4]))
					flag = 2;

				switch (flag)
				{
					case 1:
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);  // LedOn
					break;
					case 2:
					{
						//////LEDBlinking
							if (time_is_over) {
								time_is_over = 0;
								HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
							}
					}
					break;
					
					default:
						HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);  // Led_off
					
					
				}
					
			}	
			else {
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);  // Led_off
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

int commandNumber( uint8_t* temp)
{
	int result = 1;
	
		for ( int i = 1; i < sizeof( temp); i++){
		//		if((( unsigned char*)( &buf_uplevel))[i] != temp[i]){
			if(buf_uplevel[i] != temp[i]){
					result = 0;
				}	
			}
	return(result);
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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
