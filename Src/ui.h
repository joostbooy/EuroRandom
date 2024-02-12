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
	void poll();
	float read_pot(PotId);
	bool read_switch(SwitchId);

private:
	float pot_value_[NUM_POTS];
	bool sw_state_[NUM_SWITCHES];
	uint8_t debounce_[NUM_SWITCHES];

	void debounce(SwitchId, bool);
};

#endif
