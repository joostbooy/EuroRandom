#include "system.h"
#include "debug.h"
#include "dac.h"
#include "adc.h"
#include "gateIo.h"

#include "ui.h"
#include "clock.h"
#include "pulseOscillator.h"
#include "triangleOscillator.h"
#include "skewedOscillator.h"
#include "curvedOscillator.h"

Sys sys;
Adc adc;
Dac dac;
GateIo gateIo;

Ui ui;
Clock clock;
PulseOscillator pulseOscillator;
TriangleOscillator triangleOscillator;
SkewedOscillator skewedOscillator;
CurvedOscillator curvedOscillator;

bool burst = 0;
bool reset = 0;
bool trigger = 0;

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

inline void update_pots(float inc, uint32_t ticks) {
	float shifts = 1.0f - ui.read_pot(Ui::SHIFT);
	float accents = 1.0f - ui.read_pot(Ui::ACCENTS);

	triangleOscillator.update_segments(inc, ticks, ui.read_pot(Ui::TRIANGLE_FILL), accents, shifts * 0.25f);
	skewedOscillator.update_segments(inc, ticks, ui.read_pot(Ui::SKEW_FILL), accents, shifts * 0.5f);
	pulseOscillator.update_segments(inc, ticks, ui.read_pot(Ui::PULSE_FILL), accents, shifts * 0.75f);
	curvedOscillator.update_segments(inc, ticks, ui.read_pot(Ui::CURVE_FILL), accents, shifts);

	triangleOscillator.set_depth(ui.read_pot(Ui::TRIANGLE_DEPTH));
	skewedOscillator.set_amount(ui.read_pot(Ui::SKEW_AMMOUNT));
	pulseOscillator.set_width(ui.read_pot(Ui::PULSE_WIDTH));
	curvedOscillator.set_shape(ui.read_pot(Ui::CURVE_SHAPE));
}

inline void update_switches() {
	// Update reset
	bool last_reset = reset;
	reset = ui.read_switch(Ui::RESET);

	if (reset == 1 && last_reset == 0) {
		clock.reset();
		pulseOscillator.reset();
		triangleOscillator.reset();
		skewedOscillator.reset();
		curvedOscillator.reset();
	}

	// update burst
	bool last_burst = burst;
	burst = ui.read_switch(Ui::BURST);

	bool burst_insert = ui.read_switch(Ui::BURST_INSERT);
	pulseOscillator.set_burst_oscillator(!burst_insert);

	if (burst_insert == 1 && burst == 1 && last_burst == 0) {
		pulseOscillator.manual_burst();
	}

	//update trigger
	bool last_trigger = trigger;
	trigger = ui.read_switch(Ui::TRIGGER);

	bool trigger_insert = ui.read_switch(Ui::TRIGGER_INSERT);
	skewedOscillator.set_trigger_oscillator(!trigger_insert);

	if (trigger_insert == 1 && trigger == 1 && last_trigger == 0) {
		skewedOscillator.manual_trigger();
	}
}

void fill(Dac::Buffer *buffer, const size_t size) {
	Debug::write(1);

	// Update UI at 1kHz
	ui.poll();
	update_switches();

	// update clock
	clock.tick(ui.read_switch(Ui::CLOCK));
	uint32_t ticks = clock.interval() * size;
	float inc = clock.inc() * (1.f / size);

	update_pots(inc, ticks);

	// Update gate outs
	gateIo.write_clock_led(clock.phase() < 0.5f);
	gateIo.write_pulse(skewedOscillator.pulse_state());
	gateIo.write_gate(triangleOscillator.gate_state());
	gateIo.write_burst(pulseOscillator.burst_state());
	gateIo.write_noise(curvedOscillator.noise_state());

	// Update oscillators
	pulseOscillator.fill(&buffer[0].channel[0], 4, size);		// Pulse
	triangleOscillator.fill(&buffer[0].channel[1], 4, size);	// Triangle
	skewedOscillator.fill(&buffer[0].channel[2], 4, size);		// Skewed
	curvedOscillator.fill(&buffer[0].channel[3], 4, size);		// Curved

	Debug::write(0);
}

volatile uint16_t prescaler = 0;
volatile int value = 0;

int main(void)
{
	sys.init();

	Debug::init();

	gateIo.init();
	dac.init();
	adc.init();

	ui.init(&adc, &gateIo);

	clock.init();
	pulseOscillator.init();
	triangleOscillator.init();
	skewedOscillator.init();
	curvedOscillator.init();

	dac.start(&fill);

	while (1) {

	}
}
