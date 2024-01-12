#include "system.h"
#include "micros.h"
#include "debug.h"
#include "disk.h"

#include "settings.h"
#include "engine.h"
#include "ui.h"

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
	void TIM4_IRQHandler(void) {
		if (!(TIM4->SR & TIM_IT_UPDATE)) {
			return;
		}
		TIM4->SR = ~TIM_IT_UPDATE;
		//ui.poll();
	}

} //extern "C"


int main(void)
{
	sys.init();
	micros.init();	// must be called before adc, display & sdio init
	debug.init();
	disk.init();
	disk.mount();

	settings.init();	// before ui & engine
	ui.init();
	engine.init();

	// star timers

	while (1) {
		ui.process();
		engine.process();
	}
}
