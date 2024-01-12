#include "adc.h"
#include "micros.h"

Adc adc;

void Adc::init(){
	ADC_HandleTypeDef hadc1;
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	ADC_ChannelConfTypeDef sConfig = {0};


	//ADC Pins
	/**ADC1 GPIO Configuration
	PC4     ------> ADC1_IN14 -> CV 3
	PC5     ------> ADC1_IN15 -> CV 4
	PB0     ------> ADC1_IN8 -> CV 1
	PB1     ------> ADC1_IN9 -> CV 2
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	*/
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = DISABLE;
	hadc1.Init.ContinuousConvMode = DISABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 4;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	HAL_ADC_Init(&hadc1);

	// Cv 1
	sConfig.Channel = ADC_CHANNEL_8;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	// Cv 2
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = 2;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	// Cv 3
	sConfig.Channel = ADC_CHANNEL_14;
	sConfig.Rank = 3;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	// Cv 4
	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.Rank = 4;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);

	// Wait for stabilisation & begin
	__HAL_ADC_ENABLE(&hadc1);
	micros.delay(5);
	HAL_ADC_Start(&hadc1);
}
