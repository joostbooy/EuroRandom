#ifndef Ui_h
#define Ui_h

#include "adc.h"
#include "dsp.h"
#include "gateIo.h"
#include <algorithm>

class Ui {

public:

	enum SwitchId {
		BURST_INSERT,
		TRIGGER_INSERT,
		CLOCK,
		// No debounce
		RESET,
		BURST,
		TRIGGER,

		NUM_SWITCHES
	};

	enum PotId {
		SKEW_AMMOUNT,
		TRIANGLE_FILL,
		TRIANGLE_DEPTH,
		SKEW_FILL,
		PULSE_FILL,
		CURVE_SHAPE,
		PULSE_WIDTH,
		CURVE_FILL,
		ACCENTS,
		SHIFT,

		NUM_POTS
	};

	void init(Adc *adc, GateIo *gateIo);
	void poll();
	float read_pot(PotId);
	bool read_switch(SwitchId);

private:
	static const size_t kNumDebounceSwitches = 3;

	float pot_value_[NUM_POTS];
	bool sw_state_[NUM_SWITCHES];
	uint8_t sw_raw_[kNumDebounceSwitches];
	uint32_t clock_led_ticks_;

	Adc *adc_;
	GateIo *gateIo_;

	void debounce(SwitchId, bool);
};

#endif
