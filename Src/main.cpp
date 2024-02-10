#include "system.h"
#include "micros.h"
#include "debug.h"
#include "dac.h"
#include "adc.h"
#include "gateIo.h"

extern "C" {

	void NMI_Handler() { }
	void HardFault_Handler() { while (1); }
	void MemManage_Handler() { while (1); }
	void BusFault_Handler() { while (1); }
	void UsageFault_Handler() { while (1); }
	void SVC_Handler() { }
	void DebugMon_Handler() { }
	void PendSV_Handler() { }
	void SysTick_Handler(void) { }

	// 1Khz
//	void TIM2_IRQHandler(void) {
//		if (!(TIM4->SR & TIM_IT_UPDATE)) {
//			return;
//		}
//		TIM4->SR = ~TIM_IT_UPDATE;
//	}

	void DMA1_Channel5_IRQHandler(void) {

	}

} //extern "C"

int main(void)
{
	sys.init();
	micros.init();
	dac.init();
	adc.init();
	gateIo.init();
	debug.init();

	//clockReader.init();
	//oscillator.init();
	//oscillator.euclidianPattern().init();

	while (1) {

	}
}
