#ifndef TriangleOscillator_h
#define TriangleOscillator_h

#include "oscillator.h"

class TriangleOscillator : public Oscillator {

public:

	enum Stage {
		RISING,
		FALLING
	};

	void init() {
		value_ = 0.f;
		value_a_ = 0.f;
		value_b_ = 0.f;

		depth_ = 0.f;
		stage_ = RISING;
		Oscillator::init();
	}

	void reset() {
		Oscillator::reset();
	}

	void set_depth(float value) {
		depth_ = value;
	}

	void fill(uint16_t *data, const size_t inc, const size_t size) {
		for (size_t i = 0; i < size; ++i){
			*data = next_sample() * 16383;
			data += inc;
		}
	}

private:
	Stage stage_;
	float depth_;
	float value_;
	float value_a_;
	float value_b_;

	inline float next_sample() {
		float phase_ = Oscillator::phase();
		float triangle_ = triangle(phase_);
		float triangle_random_ = Dsp::cross_fade(value_a_, value_b_, triangle_);
		value_ = Dsp::cross_fade(triangle_, triangle_random_, depth_);

		Oscillator::tick();

		return value_;
	}

	inline float triangle(float phase) {
		if (phase < 0.5f) {
			set_stage(RISING);
			return phase * 2.f;
		} else {
			set_stage(FALLING);
			return (1.f - phase) * 2.f;
		}
	}

	inline void set_stage(Stage stage) {
		if (stage_ != stage) {
			stage_ = stage;

			if (stage == RISING) {
				value_a_ = value_;
				value_b_ = RandomGenerator::next_rising(value_, Oscillator::has_accent());
			} else {
				value_b_ = value_;
				value_a_ = RandomGenerator::next_falling(value_, Oscillator::has_accent());
			}
		}
	}

};

#endif
