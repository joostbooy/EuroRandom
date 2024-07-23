#ifndef PulseOscillator_h
#define PulseOscillator_h

#include "burst.h"
#include "oscillator.h"

class PulseOscillator : public Oscillator {

public:

	void init() {
		stage_ = 0;
		value_ = 0.f;
		width_ = 0.f;

		burst_state_ = 0;
		burst_oscillator_ = 0;
		burst_.init();
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

	void set_burst_oscillator(bool state) {
		burst_oscillator_ = state;
	}

	void manual_burst() {
		burst_.set(Oscillator::has_accent(), Oscillator::segment_duration());
	}

	bool burst_state() {
		return burst_state_;
	}

private:
	bool stage_;
	float width_;
	float value_;

	Burst burst_;
	bool burst_state_;
	bool burst_oscillator_;

	inline float next_sample() {
		bool accent = Oscillator::has_accent();
		float phase = Oscillator::phase();

		if ((phase < width_) && (stage_ != 0)) {
			stage_ = 0;
			value_ = RandomGenerator::next(accent);
		} else if ((phase >= width_) && (stage_ != 1)) {
			stage_ = 1;
			value_ = RandomGenerator::next(accent);
		}

		burst_state_ = burst_.tick();

		if (Oscillator::tick() && burst_oscillator_) {
			burst_.set(accent, Oscillator::segment_duration());
		}

		return value_;
	}

/*
	inline float next_sample() {
		bool accent;
		float phase;
		bool burst_state;

		float value = value_;
		float width = width_;
		bool stage = stage_;

		while (size--) {
			accent = Oscillator::has_accent();
			phase = Oscillator::phase();

			if ((phase < width) && (stage != 0)) {
				stage = 0;
				value = RandomGenerator::next(accent);
			} else if ((phase >= width_) && (stage_ != 1)) {
				stage = 1;
				value = RandomGenerator::next(accent);
			}

			burst_state_ = burst_.tick();

			if (Oscillator::tick() && burst_oscillator_) {
				burst_.set(accent, Oscillator::segment_duration());
			}

			*buffer++ = value;
		}

		value_ = value;
		stage_= stage;
		burst_state_ = burst_state;
	}
	*/
};

#endif
