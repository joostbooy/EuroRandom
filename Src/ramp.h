#ifndef Ramp_h
#define Ramp_h

#include "dsp.h"


class Ramp {

public:

	enum Mode {
		CURVE,
		RANDOM
	};

	enum Stage {
		RISING,
		FALLING
	};

	void init() {
		phase_ = 0.f;
		last_value_ = 0.f;
		target_value_ = 1.f;
		stage_ = RISING;
	}

	Stage stage() {
		return stage_;
	}

	void reset() {
		phase_ = 0.f;
	}

	float tick(Mode mode, float freq, float skew, float shape) {
		mode_ = mode;
		inc_ = freq;

		float triangle_ = triangle(phase_, skew);
		float curve_ = curve(triangle_, shape);
		value_ = Dsp::cross_fade(last_value_, target_value_, curve_);

		phase_ += inc_;
		if (phase_ >= 1.f)  {
			phase_ = 0.f;
		}

		return value_;
	}

private:

	float phase_;
	float inc_;
	float value_;
	float last_value_;
	float target_value_;
	Mode mode_;
	Stage stage_;

	inline void set_stage(Stage stage) {
		if (stage_ != stage) {
			stage_ = stage;

			last_value_ = value_;
			if (value == RISING) {
				target_value_ = mode_ == RANDOM ? Rng::reciprocal(last, 1.f) : 1.f;
			} else {
				target_value_ = mode_ == RANDOM ? Rng::reciprocal(0.f, last) : 0.f;
			}
		}
	}

	inline float triangle(float phase, float skew) {
		if (phase < skew) {
			set_stage(RISING);
			return phase * (1.0f / skew);
		} else {
			set_stage(FALLING);
			return 1.0f - (phase - skew) * (1.0f / (1.0f - skew));
		}
	}

	inline float curve(float phase, float shape) {
		uint16_t intergral = static_cast<uint16_t>(phase);
		float fractional = phase - intergral;

		const float *lut_a = &lut_exp[intergral];
		const float *lut_b = &lut_inv_exp[intergral];
		float a = Dsp::cross_fade(*lut_a, *(lut_a + 1), fractional);
		float b = Dsp::cross_fade(*lut_b, *(lut_b + 1), fractional);

		return Dsp::cross_fade(a, b, shape);
	}

};

#endif
