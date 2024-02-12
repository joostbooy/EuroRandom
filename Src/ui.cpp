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
	debounce_[id] <<= 1;
	if (state) {
		debounce_[id] |= 1;
	}

	if (debounce_[id] == 0x00 || debounce_[id] == 0xFF) {
		sw_state_[id] = debounce_[id];
	}
}

void Ui::poll() {
	debounce(BURST_INSERT, gateIo.read_burst_insert());
	debounce(TRIGGER_INSERT, gateIo.read_trigger_insert());

	if (adc.ready()) {
		int channel = adc.curr_channel();
		float in = adc.read() / 4095.f;
		float out = pot_value_[channel];

		pot_value_[channel] = Dsp::one_pole_filter(in, out, 0.05f);

		adc.convert_next_channel();
	}
}

float Ui::read_pot(PotId id) {
	return pot_value_[id];
}

bool Ui::read_switch(SwitchId id) {
	return sw_state_[id];
}
