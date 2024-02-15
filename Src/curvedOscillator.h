#ifndef CurvedOscillator_h
#define CurvedOscillator_h

#include "lookupTables.h"

class CurvedOscillator : public Oscillator {

public:

	void init() {
		value_ = 0.f;
		last_value_ = 0.f;
		target_value_ = 0.f;

		shape_ = 0.f;
		Oscillator::init();
	}

	void reset() {
		Oscillator::reset();
	}

	void set_shape(float value) {
		shape_ = value;
	}

	void fill(uint16_t *data, const size_t inc, const size_t size) {
		for (size_t i = 0; i < size; ++i){
			*data = next_sample() * 16383;
			data += inc;
		}
	}

private:
	float shape_;
	float value_;
	float last_value_;
	float target_value_;

	inline float next_sample() {
		bool accent = Oscillator::has_accent();
		float phase_ = Oscillator::phase() * (EXP_TABLE_SIZE - 1);
		float curve_ = curve(phase_, shape_);
		value_ = Dsp::cross_fade(last_value_, target_value_, curve_);

		if (Oscillator::tick()) {
			last_value_ = value_;
			target_value_ = RandomGenerator::next(accent);
		}

		return value_;
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
