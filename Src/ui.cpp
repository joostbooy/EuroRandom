#include "ui.h"

void Ui::init(Adc *adc, GateIo *gateIo) {
	adc_ = adc;
	gateIo_ = gateIo_;

	clock_led_ticks_ = 0;

	std::fill(&sw_state_[0], &sw_state_[NUM_SWITCHES], 0);
	std::fill(&pot_value_[0], &pot_value_[NUM_POTS], 0.f);
}

void Ui::debounce(SwitchId id, bool state) {
	sw_raw_[id] <<= 1;
	if (state) {
		sw_raw_[id] |= 1;
	}

	if (sw_raw_[id] == 0x80) {
		sw_state_[id] = 1;
	} else if (sw_raw_[id] == 0x01) {
		sw_state_[id] = 0;
	}
}

void Ui::poll() {
	sw_state_[RESET] = gateIo_->read_reset();
	sw_state_[BURST] = gateIo_->read_burst();
	sw_state_[TRIGGER] = gateIo_->read_trigger();

	debounce(BURST_INSERT, gateIo_->read_burst_insert());
	debounce(TRIGGER_INSERT, gateIo_->read_trigger_insert());
	debounce(CLOCK, gateIo_->read_clock());

	if (adc_->ready()) {
		int channel = adc_->curr_channel();
		float in = adc_->read() / 4095.f;
		float out = pot_value_[channel];

		pot_value_[channel] = Dsp::one_pole_filter(in, out, 0.05f);
		adc_->convert_next_channel();
	}
}

float Ui::read_pot(PotId id) {
	return pot_value_[id];
}

bool Ui::read_switch(SwitchId id) {
	return sw_state_[id];
}
