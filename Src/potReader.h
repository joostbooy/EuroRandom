#ifndef PotReader_h
#define PotReader_h

class PotReader {

public:

	enum Id {
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

	void init() {
		for (int i = 0; i < NUM_POTS; ++i) {
			value_[i] 0.f;
		}
	}

	void poll() {
		if (adc.ready()) {
			int channel = adc.curr_channel();
			float in = adc.read() / 4095.f;
			float out = value_[chn];

			value_[chn] = Dsp::one_pole_filter(in, out, 0.05f);

			adc.convert_next_channel();
		}
	}

	float read(Id id) {
		return value_[id];
	}

private:
	float value_[NUM_POTS];
};

#endif
