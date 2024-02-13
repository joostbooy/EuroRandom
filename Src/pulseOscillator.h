#ifndef PulseOscillator_h
#define PulseOscillator_h

#include "oscillator.h"
#include "rng.h"

class PulseOscillator {

public:

	void init() {
		stage_ = 0;
		value_ = 0.f;
		width_ = 0.f;
		oscillator_.init();
	}

	void reset() {
		stage_ = 0;
		oscillator_.reset();
	}

	void set_segment_ticks(uint32_t value) {
		oscillator_.set_segment_ticks(value);
	}

	EuclidianPattern &euclidianPattern() {
		return oscillator_.euclidianPattern();
	}

	void set_width(float value) {
		width_ = value;
	}

	float tick() {
		float phase = oscillator_.phase();

		if ((phase < width_) && (stage_ != 0)) {
			stage_ = 0;
			value_ = Rng::reciprocal();
		} else if ((phase >= width_) && (stage_ != 1)) {
			stage_ = 1;
			value_ = Rng::reciprocal();
		}

		oscillator_.tick();

		return value_;
	}

private:
	bool stage_;
	float width_;
	float value_;
	Oscillator oscillator_;
};

#endif
