#ifndef PulseOscillator_h
#define PulseOscillator_h

#include "oscillator.h"
#include "rng.h"

class PulseOscillator : public Oscillator {

public:

	void init() {
		stage_ = 0;
		value_ = 0.f;
		width_ = 0.f;
		Oscillator::init();
	}

	void reset() {
		stage_ = 0;
		Oscillator::reset();
	}

	void set_width(float value) {
		width_ = value;
	}

	void fill(uint16_t *data, const size_t inc, const size_t size) {
		for (size_t i = 0; i < size; ++i){
			*data = next_sample() * 16383;
			data += inc;
		}
	}

private:
	bool stage_;
	float width_;
	float value_;

	inline float next_sample() {
		float gain_ = Oscillator::gain();
		float phase = Oscillator::phase();

		if ((phase < width_) && (stage_ != 0)) {
			stage_ = 0;
			value_ = Rng::reciprocal();
		} else if ((phase >= width_) && (stage_ != 1)) {
			stage_ = 1;
			value_ = Rng::reciprocal();
		}

		Oscillator::tick();

		return value_ * gain_;
	}
};

#endif
