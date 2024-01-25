#ifndef CurvedOscillator_h
#define CurvedOscillator_h

class CurvedOscillator {

public:

	void init() {
		value_ = 0.f;
		last_value_ = 0.f;
		target_value_ 0.f;

		shape_ = 0.f;
		oscillator_.init();
	}

	void reset() {
		oscillator_.reset();
	}

	EuclidianPattern &euclidianPattern() {
		return oscillator_.euclidianPattern();
	}

	void set_shape(float value) {
		shape_ = value;
	}

	float tick() {
		float phase_ = oscillator_.phase();
		float curve_ = curve(phase_, shape_);
		value_ = Dsp::cross_fade(last_value_, target_value_, curve_);

		if (oscillator_.tick()) {
			last_value_ = value_;
			target_value_ = Rng::reciprocal();
		}
	}

private:
	float shape_;
	float value_;
	float last_value_;
	float target_value_;
	Oscillator oscillator_;

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
