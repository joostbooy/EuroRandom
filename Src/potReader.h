#ifndef PotReader_h
#define PotReader_h

class PotReader {

public:

	enum Id {
		CURVE_SHAPE,
		CURVE_FILL,
		PULSE_WIDTH,
		PULSE_FILL,
		SKEW_AMMOUNT,
		SKEW_FILL,
		TRIANGLE_DEPTH,
		TRIANGLE_FILL,
		ACCENTS,
		SHIFT,

		NUM_POTS
	};

	void init() {
		for (int i = 0; i < NUM_POTS; ++i) {
			value_[i] 0.f;
		}
	}

	void update() {
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
