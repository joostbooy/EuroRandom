#ifndef TriangleOscillator_h
#define TriangleOscillator_h

#include "oscillator.h"

class TriangleOscillator : public Oscillator {

public:

	void init() {
		value_ = 0.f;
		last_value_ = 0.f;
		target_value_ = 0.f;

		depth_ = 0.f;
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
	bool stage_;
	float depth_;
	float value_;
	float last_value_;
	float target_value_;

	inline float next_sample() {
		float gain_ = Oscillator::gain();
		float phase_ = Oscillator::phase();
		float triangle_ = triangle(phase_);
		float triangle_random_ = Dsp::cross_fade(last_value_, target_value_, triangle_);
		value_ = Dsp::cross_fade(triangle_, triangle_random_, depth_);

		Oscillator::tick();

		return value_ * gain_;
	}

	inline float triangle(float phase) {
		if (phase < 0.5f) {
			set_stage(0);
			return phase * 2.f;
		} else {
			set_stage(1);
			return (1.f - phase) * 2.f;
		}
	}

	inline void set_stage(bool stage) {
		if (stage_ != stage) {
			stage_ = stage;

			if (stage) {
				target_value_ = value_;
				last_value_ = get_random(0.f, last_value_);
			} else {
				last_value_ = value_;
				target_value_ = get_random(last_value_, 1.f);
			}
		}
	}

	inline float get_random(float min , float max) {
		return Rng::reciprocal() * (max - min) + min;
	}
};

#endif
