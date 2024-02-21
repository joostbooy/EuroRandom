#include "system.h"

Sys sys;

void Sys::init() {
	//GPIO Ports Clock Enable
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//Periparel Clock Enable
	__HAL_RCC_DMA1_CLK_ENABLE();
	__HAL_RCC_ADC1_CLK_ENABLE();
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();
	//__HAL_RCC_TIM2_CLK_ENABLE();

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

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
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/** Initializes the CPU, AHB and APB buses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
	|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_ADC1;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
	PeriphClkInit.Adc1ClockSelection = RCC_ADC1PLLCLK_DIV1;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

	// Interupt priorities
	//HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	//HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);	// Dac
	//HAL_NVIC_SetPriority(TIM2_IRQn, 1, 0);			// Ui Poll
}
