#ifndef Ui_h
#define Ui_h

#include "que.h"
#include "adc.h"
#include "dsp.h"
#include "gateIo.h"

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

	void init();
	void update_swiches();
	bool update_pots();
	void update_clock_led(uint32_t);
	void reset_clock_led();
	bool read_switch(SwitchId);
	float read_pot(PotId);

private:
	static const size_t kNumDebounceSwitches = 3;

	uint32_t clock_led_ticks_;
	float pot_value_[NUM_POTS];
	bool sw_state_[NUM_SWITCHES];
	uint8_t sw_raw_[kNumDebounceSwitches];

	void debounce(SwitchId, bool);
};

#endif
