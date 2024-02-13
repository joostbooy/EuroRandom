#include "system.h"
#include "micros.h"
#include "debug.h"
#include "dac.h"
#include "adc.h"
#include "gateIo.h"

#include "ui.h"
#include "clockReader.h"
#include "pulseOscillator.h"
#include "triangleOscillator.h"
#include "skewedOscillator.h"
#include "curvedOscillator.h"

Ui ui;
ClockReader clockReader;
PulseOscillator pulseOscillator;
TriangleOscillator triangleOscillator;
SkewedOscillator skewedOscillator;
CurvedOscillator curvedOscillator;

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

} //extern "C"

uint8_t ui_prescaler = 0;

void fill(Dac::Buffer *buffer, const size_t size) {
	// Update ui
	ui.update_pots();

	if (!(++ui_prescaler & 3)) {
		ui.update_swiches();
	}

	// Update clock
	clockReader.tick(ui.read_switch(Ui::CLOCK));

	pulseOscillator.set_segment_ticks(clockReader.interval());
	triangleOscillator.set_segment_ticks(clockReader.interval());
	skewedOscillator.set_segment_ticks(clockReader.interval());
	curvedOscillator.set_segment_ticks(clockReader.interval());

	// Set trigger outs
	gateIo.write_burst(0);
	gateIo.write_trigger(0);
	gateIo.write_gate(0);
	gateIo.write_noise(0);

	// Render oscillators
	for (size_t i = 0; i < size; ++i) {
		buffer[i].channel[0] = pulseOscillator.tick();		// Pulse
		buffer[i].channel[1] = triangleOscillator.tick();	// Triangle
		buffer[i].channel[2] = skewedOscillator.tick();		// Skew
		buffer[i].channel[3] = curvedOscillator.tick();		// Curve
	}
}

int main(void)
{
	sys.init();
	micros.init();
	adc.init();
	dac.init();
	gateIo.init();
	debug.init();

	ui.init();

	pulseOscillator.init();
	triangleOscillator.init();
	skewedOscillator.init();
	curvedOscillator.init();

	dac.start(&fill);

	while (1) {

	}
}
