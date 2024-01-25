#ifndef SkewedOscillator_h
#define SkewedOscillator_h

#include "oscillator.h"

class SkewedOscillator {

public:

	void init() {
		stage_ = 0;
		value_ = 0.f;
		last_value_ = 0.f;
		target_value_ 0.f;

		ammount_ = 0.f;
		oscillator_.init();
	}

	void reset() {
		oscillator_.reset();
	}

	EuclidianPattern &euclidianPattern() {
		return oscillator_.euclidianPattern();
	}

	void set_ammount(float value) {
		ammount_ = value;
	}

	float tick() {
		float phase_ = oscillator_.phase();
		float skew_ = skew(phase_, ammount_);
		value_ = Dsp::cross_fade(last_value_, target_value_, skew_);

		oscillator_.tick();

		return value_;
	}

private:
	bool stage_;
	float ammount_;
	float value_;
	float last_value_;
	float target_value_;
	Oscillator oscillator_;

	inline float skew(float phase, float ammount) {
		if (phase < ammount) {
			set_stage(0);
			return phase * (1.0f / ammount);
		} else {
			set_stage(1);
			return (phase - ammount) * (1.0f / (1.0f - ammount));
		}
	}

	inline void set_stage(bool stage) {
		if (stage_ != stage) {
			stage_ = stage;
			last_value_ = value_;
			target_value_ = Rng::reciprocal();
		}
	}
};

#endif
