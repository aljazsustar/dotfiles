/* USER CODE BEGIN Header */
/**
    ******************************************************************************
    * @file                     : main.c
    * @brief                    : Main program body
    ******************************************************************************
    * @attention
    *
    * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
    * All rights reserved.</center></h2>
    *
    * This software component is licensed by ST under BSD 3-Clause license,
    * the "License"; You may not use this file except in compliance with the
    * License. You may obtain a copy of the License at:
    *                                                opensource.org/licenses/BSD-3-Clause
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

// a struct that defines a GPIO device (maps GPIOs memory structure)
typedef struct
{
    uint32_t mode_r;
    uint32_t out_type_r;
    uint32_t out_speed_r;
    uint32_t pu_pd_r;
    uint32_t input_data_r;
    uint32_t output_data_r;
    uint16_t bit_set_r;
    uint16_t bit_reset_r;
} GPIO_device;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/

/* USER CODE BEGIN PD */

// constants for storing addresses of GPIOs
#define GPIOAd ((GPIO_device*)0x40020000)
#define GPIOBd (0x40020400)
#define GPIOCd (0x40020800)
#define GPIODd ((GPIO_device*)0x40020C00)
#define GPIOEd (0x40021000)
#define GPIOFd (0x40021400)
#define GPIOGd (0x40021800)
#define GPIOHd (0x40021C00)
#define GPIOId (0x40022000)

// system clock address
#define CLK ((uint32_t*) 0x40023830)

// MODE constants
#define IN (uint32_t) 0x0
#define OUT (uint32_t) 0x1
#define AF (uint32_t) 0x2
#define ANALOG (uint32_t) 0x3

// PUPD constants
#define NO_PULL (uint32_t) 0x0
#define PULL_UP (uint32_t) 0x1
#define PULL_DOWN (uint32_t) 0x2

// OTYPE constants
#define PUSH_PULL (uint32_t) 0x0
#define OPEN_DRAIN (uint32_t) 0x1

// OSPEED constants
#define S2MHz (uint32_t) 0x0
#define S25MHz (uint32_t) 0x1
#define S50MHz (uint32_t) 0x2
#define S100MHz (uint32_t) 0x3

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

void clock_on(GPIO_device * GPIO_addr);
void init_GPIO(GPIO_device * GPIO_addr, uint32_t Pin, uint32_t Mode, uint32_t PUPD, uint32_t OType, uint32_t OSpeed);
void GPIO_pin_write(GPIO_device * GPIO_addr, uint32_t Pin, uint32_t val);
uint32_t GPIO_pin_read(GPIO_device * GPIO_addr, uint32_t Pin);
void delay(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
    * @brief    The application entry point.
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
    /* USER CODE BEGIN 2 */

    // turn on button's GPIO (button is on PA0)
    clock_on(GPIOAd);

    // turn on led's GPIO (leds are on PD12, PD13, PD14, PD15)
    clock_on((GPIO_device*)GPIODd);


    // init button
    init_GPIO((GPIO_device*) GPIOAd, 0, IN, PUSH_PULL, NO_PULL, S2MHz);

    // init leds
    for (int i = 12; i < 16; i++)
    	init_GPIO((GPIO_device*) GPIODd, i, OUT, PUSH_PULL, NO_PULL, S2MHz);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        // read button and trigger led sequence
        if (GPIO_pin_read((GPIO_device*)GPIOAd, 0) == 1) {
        	for (int i = 12; i < 16; i++) {
        		GPIO_pin_write((GPIO_device*) GPIODd, i, 1);
        		delay();
        	}
        }

        for (int i = 12; i < 16; i++) GPIO_pin_write((GPIO_device*) GPIODd, i, 0);

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
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
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

// function for turning on a particular GPIO (enables the port clock)
void clock_on(GPIO_device * GPIO_addr)
{

	unsigned long offset = ((unsigned long)GPIO_addr - (unsigned long) GPIOAd) / 0x400;
	*CLK = *CLK | (unsigned long)1 << offset;
}

// function for initializing GPIOs
void init_GPIO(GPIO_device * GPIO_addr, uint32_t Pin, uint32_t Mode, uint32_t PUPD, uint32_t OType, uint32_t OSpeed)
{
	// set bits to 0 before set
	// 2 * pin because 2 bits are used to set each pin
	// set mode
    GPIO_addr -> mode_r = GPIO_addr -> mode_r & ~(3 << (2 * Pin));
    GPIO_addr -> mode_r = GPIO_addr -> mode_r | (Mode << 2 * Pin);


    // set pull-up/pull-down
    GPIO_addr -> pu_pd_r = GPIO_addr -> pu_pd_r & ~(3 << (2 * Pin));
    GPIO_addr -> out_type_r = GPIO_addr -> out_type_r | (OType << (2 * Pin));

    // set output speed
    GPIO_addr -> out_speed_r = GPIO_addr -> pu_pd_r & ~(3 << (2 * Pin));
    GPIO_addr -> out_type_r = GPIO_addr -> out_type_r | (OSpeed << (2 * Pin));

    // set output type
    // this one only uses 1 bit
    GPIO_addr -> out_type_r = GPIO_addr -> out_type_r & ~(1 << Pin);
    GPIO_addr -> out_type_r = GPIO_addr -> out_type_r | (OType << (Pin));


}

// function for setting the value of an output GPIO pin
void GPIO_pin_write(GPIO_device * GPIO_addr, uint32_t Pin, uint32_t val)
{
    if (val == 1) {
    	GPIO_addr -> bit_set_r = GPIO_addr -> bit_set_r | (1 << Pin);
    } else {
    	GPIO_addr -> bit_reset_r = GPIO_addr -> bit_reset_r | (1 << Pin);
    }
}

// function for reading the value of an input GPIO pin
uint32_t GPIO_pin_read(GPIO_device * GPIO_addr, uint32_t Pin)
{
    return GPIO_addr -> input_data_r & (1 << Pin);
}

// hardcoded delay
void delay(void) {
    volatile int d = 500000;
    while(d--);
}

/* USER CODE END 4 */

/**
    * @brief    This function is executed in case of error occurrence.
    * @retval None
    */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef    USE_FULL_ASSERT
/**
    * @brief    Reports the name of the source file and the source line number
    *                 where the assert_param error has occurred.
    * @param    file: pointer to the source file name
    * @param    line: assert_param error line source number
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
