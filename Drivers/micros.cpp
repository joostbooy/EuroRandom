#include "micros.h"

Micros micros;

void Micros::init() {
	TIM_HandleTypeDef TimHandle;

	TimHandle.Instance = TIM5;
	TimHandle.Init.Prescaler = (F_CPU / 1000000 / 4) - 1;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TimHandle.Init.Period = 0xFFFFFFFF;
	TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

	HAL_TIM_Base_Init(&TimHandle);
	HAL_TIM_Base_Start(&TimHandle);
}
