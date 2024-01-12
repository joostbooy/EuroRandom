#include "timer.h"

Timer timer;

void Timer::start_2(uint32_t freq){
	TIM_HandleTypeDef TimHandle;

	TimHandle.Instance               = TIM2;
	TimHandle.Init.Period            = (F_CPU / freq / 2) - 1;
	TimHandle.Init.Prescaler         = 0;
	TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&TimHandle);
	HAL_TIM_Base_Start_IT(&TimHandle);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void Timer::start_3(uint32_t freq){
	TIM_HandleTypeDef TimHandle;

	TimHandle.Instance               = TIM3;
	TimHandle.Init.Period            = (F_CPU / freq / 2) - 1;
	TimHandle.Init.Prescaler         = 0;
	TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&TimHandle);
	HAL_TIM_Base_Start_IT(&TimHandle);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void Timer::start_4(uint32_t freq) {
	TIM_HandleTypeDef TimHandle;

	TimHandle.Instance               = TIM4;
	TimHandle.Init.Period            = (F_CPU / freq / 4) - 1;
	TimHandle.Init.Prescaler         = 1;
	TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
	TimHandle.Init.RepetitionCounter = 0;
	TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&TimHandle);
	HAL_TIM_Base_Start_IT(&TimHandle);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
}
