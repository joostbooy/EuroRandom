#ifndef Ramp_h
#define Ramp_h

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
		last_ = 0.f;
		next_ = 1.f;
		stage_ = RISING;
	}

	Stage stage() {
		return stage_;
	}

	float tick(Mode mode, float skew, float shape) {
		float triangle_ = triangle(phase_, skew);
		float curve_ = curve(triangle_, shape);
		float value_ = Dsp::cross_fade(last_, next_, curve_);

		phase_ += inc_;
		if (phase_ >= 1.f)  {
			phase_ = 0.f;
		}

		return value_;
	}


private:

	float phase_;
	float inc_;
	float next_;
	float last_;
	Stage stage_;

	inline void set_stage(Stage stage, Mode mode) {
		if (stage_ != stage) {
			stage_ = stage;

			last_ = value_;
			if (value == RISING) {
				next_ = mode == RANDOM ? Rng::reciprocal(last, 1.f) : 1.f;
			} else {
				next_ = mode == RANDOM ? Rng::reciprocal(0.f, last) : 0.f;
			}
		}
	}

	inline float triangle(float phase, float skew) {
		if (phase < skew) {
			float inc_up = 1.0f / skew;
			return phase * inc_up;
		} else {
			float inc_down = 1.0f / (1.0f - skew);
			return 1.0f - (phase - skew) * inc_down;
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
