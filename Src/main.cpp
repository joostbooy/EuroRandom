#include "system.h"
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


//for (size_t i = 0; i < size; ++i) {
//	buffer[i].channel[0] = pulseOscillator.next_sample() * 16383;		// Pulse
//	buffer[i].channel[1] = triangleOscillator.next_sample() * 16383;	// Triangle
//	buffer[i].channel[2] = skewedOscillator.next_sample() * 16383;		// Skewed
//	buffer[i].channel[3] = curvedOscillator.next_sample() * 16383;		// Curved
//}


bool reset = 0;
uint8_t sw_prescaler = 0;

void fill(Dac::Buffer *buffer, const size_t size) {
	// Update switches
	if (++sw_prescaler >= 12) {
		sw_prescaler = 0;
		ui.update_swiches();
	}

	// Update clock interval
	clockReader.tick(ui.read_switch(Ui::CLOCK));
	uint32_t interval = clockReader.interval();
	uint32_t ticks = size * interval;

	ui.update_clock_led(interval);

	// Update pots
	ui.update_pots();
	float shifts = ui.read_pot(Ui::SHIFT);
	float accents = ui.read_pot(Ui::ACCENTS);

	triangleOscillator.update_segments(ticks, ui.read_pot(Ui::TRIANGLE_FILL), accents, shifts * 0.25f);
	skewedOscillator.update_segments(ticks, ui.read_pot(Ui::SKEW_FILL), accents, shifts * 0.5f);
	pulseOscillator.update_segments(ticks, ui.read_pot(Ui::PULSE_FILL), accents, shifts * 0.75f);
	curvedOscillator.update_segments(ticks, ui.read_pot(Ui::CURVE_FILL), accents, shifts);

	triangleOscillator.set_depth(ui.read_pot(Ui::TRIANGLE_DEPTH));
	skewedOscillator.set_amount(ui.read_pot(Ui::SKEW_AMMOUNT));
	pulseOscillator.set_width(ui.read_pot(Ui::PULSE_WIDTH));
	curvedOscillator.set_shape(ui.read_pot(Ui::CURVE_SHAPE));

	// Update reset
	bool last_reset = reset;
	reset = ui.read_switch(Ui::RESET);

	if (reset == 1 && last_reset == 0) {
		pulseOscillator.reset();
		triangleOscillator.reset();
		skewedOscillator.reset();
		curvedOscillator.reset();

		ui.reset_clock_led();
	}

	// Set trigger outs
	gateIo.write_burst(0);
	gateIo.write_trigger(0);
	gateIo.write_gate(0);
	gateIo.write_noise(0);

	//	if (ui.read_switch(Ui::TRIGGER_INSERT)) {
	//		triggerOut.tick(ui.read_switch(Ui::TRIGGER));
	//	} else {
	//		triggerOut.tick();
	//	}


	// Render oscillators
	pulseOscillator.fill(&buffer[0].channel[0], 4, size);		// Pulse
	triangleOscillator.fill(&buffer[0].channel[1], 4, size);	// Triangle
	skewedOscillator.fill(&buffer[0].channel[2], 4, size);		// Skewed
	curvedOscillator.fill(&buffer[0].channel[3], 4, size);		// Curved
}

int main(void)
{
	sys.init();
	adc.init();
	dac.init();
	gateIo.init();
	debug.init();

	ui.init();
	//triggerOut.init();
	clockReader.init();
	pulseOscillator.init();
	triangleOscillator.init();
	skewedOscillator.init();
	curvedOscillator.init();

	dac.start(&fill);

	while (1) {
		//
	}
}
