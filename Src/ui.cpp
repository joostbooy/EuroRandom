#include "ui.h"

void Ui::init() {
	for (int i = 0; i < NUM_SWITCHES; ++i) {
		sw_state_[i] = 0;
	}

	for (int i = 0; i < NUM_POTS; ++i) {
		pot_value_[i] = 0.f;
	}
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

void Ui::update_pots() {
	if (adc.ready()) {
		int channel = adc.curr_channel();
		float in = adc.read() / 4095.f;
		float out = pot_value_[channel];

		pot_value_[channel] = Dsp::one_pole_filter(in, out, 0.05f);

		adc.convert_next_channel();
	}
}

void Ui::update_swiches() {
	sw_state_[RESET] = gateIo.read_reset();
	sw_state_[BURST] = gateIo.read_burst();
	sw_state_[TRIGGER] = gateIo.read_trigger();

	debounce(BURST_INSERT, gateIo.read_burst_insert());
	debounce(TRIGGER_INSERT, gateIo.read_trigger_insert());
	debounce(CLOCK, gateIo.read_clock());
}

float Ui::read_pot(PotId id) {
	return pot_value_[id];
}

bool Ui::read_switch(SwitchId id) {
	return sw_state_[id];
}
