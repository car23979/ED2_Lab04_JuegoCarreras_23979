/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

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

/* USER CODE BEGIN PV */
volatile uint8_t puntosJ1 = 0;
volatile uint8_t puntosJ2 = 0;
volatile uint8_t carrera_activa = 0; // Bloquea botones hasta que termine conteo
volatile uint8_t hay_ganador = 0;

// Antirebote
volatile uint32_t last_tick_J1 = 0;
volatile uint32_t last_tick_J2 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void mostrarEnDisplay(uint8_t num);
void verificar_ganador(void);
void actualizar_leds_carrera_J1(uint8_t pos);
void actualizar_leds_carrera_J2(uint8_t pos);
void apagar_todo_emergencia(void);

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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Detectar botón de inicio (BTN_3 en PC2)

	  if (HAL_GPIO_ReadPin(BTN_INICIO_GPIO_Port, BTN_INICIO_Pin) == GPIO_PIN_RESET && !carrera_activa) {
		  // LIMPIEZA TOTAL DE REGISTROS
		      GPIOB->ODR = 0; // Apaga todos los pines del Puerto B de un solo golpe
		      GPIOC->ODR = 0; // Apaga todos los pines del Puerto C de un solo golpe (Esto mata a PC4)

		      // El display es Ánodo Común, así que después de limpiar ODR,
		      // hay que volver a apagarlo (enviando 1s)
		      HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_B_Pin|Seg_C_Pin|Seg_D_Pin|Seg_E_Pin|Seg_F_Pin|Seg_G_Pin, GPIO_PIN_SET);

		      puntosJ1 = 0;
		      puntosJ2 = 0;
		      hay_ganador = 0;

	      for (int i = 5; i >= 0; i--) {
	          mostrarEnDisplay(i);
	          HAL_Delay(100);
	      }
	      carrera_activa = 1;
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
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
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(J2_LED2_GPIO_Port, J2_LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, Seg_C_Pin|Seg_B_Pin|Seg_G_Pin|Seg_A_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, J1_LED2_Pin|J1_LED1_Pin|J2_LED1_Pin|J1_LED4_Pin
                          |J1_LED3_Pin|J2_LED3_Pin|J2_LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Seg_F_GPIO_Port, Seg_F_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Seg_E_Pin|Seg_D_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_J1_Pin BTN_J2_Pin */
  GPIO_InitStruct.Pin = BTN_J1_Pin|BTN_J2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : BTN_INICIO_Pin */
  GPIO_InitStruct.Pin = BTN_INICIO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN_INICIO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin Seg_E_Pin Seg_D_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|Seg_E_Pin|Seg_D_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : J2_LED2_Pin Seg_C_Pin Seg_B_Pin Seg_G_Pin
                           Seg_A_Pin */
  GPIO_InitStruct.Pin = J2_LED2_Pin|Seg_C_Pin|Seg_B_Pin|Seg_G_Pin
                          |Seg_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : J1_LED2_Pin J1_LED1_Pin Seg_F_Pin J2_LED1_Pin
                           J1_LED4_Pin J1_LED3_Pin J2_LED3_Pin J2_LED4_Pin */
  GPIO_InitStruct.Pin = J1_LED2_Pin|J1_LED1_Pin|Seg_F_Pin|J2_LED1_Pin
                          |J1_LED4_Pin|J1_LED3_Pin|J2_LED3_Pin|J2_LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (!carrera_activa || hay_ganador) return;

    // JUGADOR 1
    if (GPIO_Pin == BTN_J1_Pin) {
        // Solo contamos si el pin está realmente en nivel bajo (presionado)
        // y si ha pasado suficiente tiempo (debounce)
        if (HAL_GPIO_ReadPin(BTN_J1_GPIO_Port, BTN_J1_Pin) == GPIO_PIN_RESET) {
            if (HAL_GetTick() - last_tick_J1 > 250) {
                puntosJ1++;
                actualizar_leds_carrera_J1(puntosJ1);
                verificar_ganador();
                last_tick_J1 = HAL_GetTick();
            }
        }
    }

    // JUGADOR 2
    if (GPIO_Pin == BTN_J2_Pin) {
        if (HAL_GPIO_ReadPin(BTN_J2_GPIO_Port, BTN_J2_Pin) == GPIO_PIN_RESET) {
            if (HAL_GetTick() - last_tick_J2 > 250) {
                puntosJ2++;
                actualizar_leds_carrera_J2(puntosJ2);
                verificar_ganador();
                last_tick_J2 = HAL_GetTick();
            }
        }
    }
}

void verificar_ganador(void) {
    if (puntosJ1 >= 4) {
        hay_ganador = 1;
        carrera_activa = 0;
        mostrarEnDisplay(1);

        // --- GANADOR JUGADOR 1 ---
        // 1. Encender TODOS los de J1 (Cuidado: J1_LEDx pueden estar en puertos distintos)
        HAL_GPIO_WritePin(J1_LED1_GPIO_Port, J1_LED1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(J1_LED2_GPIO_Port, J1_LED2_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(J1_LED3_GPIO_Port, J1_LED3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(J1_LED4_GPIO_Port, J1_LED4_Pin, GPIO_PIN_SET);

        // 2. Apagar TODOS los de J2 (Aquí forzamos el apagado de PC4 específicamente)
        HAL_GPIO_WritePin(J2_LED1_GPIO_Port, J2_LED1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(J2_LED2_GPIO_Port, J2_LED2_Pin, GPIO_PIN_RESET); // Este suele ser PC4
        HAL_GPIO_WritePin(J2_LED3_GPIO_Port, J2_LED3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(J2_LED4_GPIO_Port, J2_LED4_Pin, GPIO_PIN_RESET);
    }
    else if (puntosJ2 >= 4) {
        hay_ganador = 1;
        carrera_activa = 0;
        mostrarEnDisplay(2);

        // --- GANADOR JUGADOR 2 ---
        // 1. Encender TODOS los de J2 (Incluyendo PC4)
        HAL_GPIO_WritePin(J2_LED1_GPIO_Port, J2_LED1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(J2_LED2_GPIO_Port, J2_LED2_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(J2_LED3_GPIO_Port, J2_LED3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(J2_LED4_GPIO_Port, J2_LED4_Pin, GPIO_PIN_SET);

        // 2. Apagar TODOS los de J1
        HAL_GPIO_WritePin(J1_LED1_GPIO_Port, J1_LED1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(J1_LED2_GPIO_Port, J1_LED2_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(J1_LED3_GPIO_Port, J1_LED3_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(J1_LED4_GPIO_Port, J1_LED4_Pin, GPIO_PIN_RESET);
    }
}

void mostrarEnDisplay(uint8_t num) {
    // Apagar todos primero (SET = OFF en Ánodo Común)
    HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_B_Pin|Seg_C_Pin|Seg_D_Pin|Seg_E_Pin|Seg_F_Pin|Seg_G_Pin, GPIO_PIN_SET);

    switch(num) {
        case 0: HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_B_Pin|Seg_C_Pin|Seg_D_Pin|Seg_E_Pin|Seg_F_Pin, GPIO_PIN_RESET); break;
        case 1: HAL_GPIO_WritePin(Seg_B_GPIO_Port, Seg_B_Pin|Seg_C_Pin, GPIO_PIN_RESET); break;
        case 2: HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_B_Pin|Seg_G_Pin|Seg_E_Pin|Seg_D_Pin, GPIO_PIN_RESET); break;
        case 3: HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_B_Pin|Seg_G_Pin|Seg_C_Pin|Seg_D_Pin, GPIO_PIN_RESET); break;
        case 4: HAL_GPIO_WritePin(Seg_F_GPIO_Port, Seg_F_Pin|Seg_G_Pin|Seg_B_Pin|Seg_C_Pin, GPIO_PIN_RESET); break;
        case 5: HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_F_Pin|Seg_G_Pin|Seg_C_Pin|Seg_D_Pin, GPIO_PIN_RESET); break;
    }
}

void actualizar_leds_carrera_J1(uint8_t pos) {
    HAL_GPIO_WritePin(J1_LED1_GPIO_Port, J1_LED1_Pin|J1_LED2_Pin|J1_LED3_Pin|J1_LED4_Pin, GPIO_PIN_RESET);
    if(pos == 1) HAL_GPIO_WritePin(J1_LED1_GPIO_Port, J1_LED1_Pin, GPIO_PIN_SET);
    if(pos == 2) HAL_GPIO_WritePin(J1_LED2_GPIO_Port, J1_LED2_Pin, GPIO_PIN_SET);
    if(pos == 3) HAL_GPIO_WritePin(J1_LED3_GPIO_Port, J1_LED3_Pin, GPIO_PIN_SET);
    if(pos == 4) HAL_GPIO_WritePin(J1_LED4_GPIO_Port, J1_LED4_Pin, GPIO_PIN_SET);
}

void actualizar_leds_carrera_J2(uint8_t pos) {
    HAL_GPIO_WritePin(J2_LED1_GPIO_Port, J2_LED1_Pin|J2_LED2_Pin|J2_LED3_Pin|J2_LED4_Pin, GPIO_PIN_RESET);
    if(pos == 1) HAL_GPIO_WritePin(J2_LED1_GPIO_Port, J2_LED1_Pin, GPIO_PIN_SET);
    if(pos == 2) HAL_GPIO_WritePin(J2_LED2_GPIO_Port, J2_LED2_Pin, GPIO_PIN_SET);
    if(pos == 3) HAL_GPIO_WritePin(J2_LED3_GPIO_Port, J2_LED3_Pin, GPIO_PIN_SET);
    if(pos == 4) HAL_GPIO_WritePin(J2_LED4_GPIO_Port, J2_LED4_Pin, GPIO_PIN_SET);
}

void apagar_todo_emergencia(void) {
    // Apagar J1
    HAL_GPIO_WritePin(J1_LED1_GPIO_Port, J1_LED1_Pin | J1_LED2_Pin | J1_LED3_Pin | J1_LED4_Pin, GPIO_PIN_RESET);

    // Apagar J2 (Aquí es donde PC4 podría estar fallando si no usas su etiqueta correcta)
    // Asegúrate que J2_LED2 (o el que sea PC4) esté en esta lista:
    HAL_GPIO_WritePin(J2_LED1_GPIO_Port, J2_LED1_Pin | J2_LED2_Pin | J2_LED3_Pin | J2_LED4_Pin, GPIO_PIN_RESET);

    // Apagar Display (Ánodo común = SET para apagar)
    HAL_GPIO_WritePin(Seg_A_GPIO_Port, Seg_A_Pin|Seg_B_Pin|Seg_C_Pin|Seg_D_Pin|Seg_E_Pin|Seg_F_Pin|Seg_G_Pin, GPIO_PIN_SET);
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
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
