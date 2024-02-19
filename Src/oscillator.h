#ifndef Oscillator_h
#define Oscillator_h

#include "dsp.h"
#include "randomGenerator.h"
#include "euclidianPattern.h"


class Oscillator {

public:

	void init() {
		inc_ = 0.1;
		phase_ = 0.f;
		accent_ = 0;
		segment_ticks_ = 16000;

		euclidianPattern_.init();
		euclidianAccentPattern_.init();
	}

	void update_segments(uint32_t ticks, float fill, float accents, float shifts) {
		int pulses_ = fill * 32;
		int shifts_ = pulses_ * shifts;
		int accents_ = pulses_ * accents;

		euclidianPattern_.update(32, pulses_, shifts);
		euclidianAccentPattern_.update(pulses_, accents_, shifts_);

		segment_ticks_ = ticks;
	}

	void reset() {
		phase_ = 0.f;
		euclidianPattern_.reset();
		euclidianAccentPattern_.reset();
	}

	uint32_t segment_duration() {
		return segment_duration_;
	}

	float phase() {
		return phase_;
	}

	bool has_accent() {
		return accent_;
	}

	bool tick() {
		phase_ += inc_;
		if (phase_ >= 1.f)  {
			phase_ = 0.f;
			accent_ = euclidianAccentPattern_.next_trigger();
			segment_duration_ = euclidianPattern_.next_duration() * segment_ticks_;
			inc_ = 1.f / segment_duration_;
			return true;
		}

		return false;
	}

private:
	float inc_;
	float phase_;
	bool accent_;
	uint32_t segment_ticks_;
	uint32_t segment_duration_;
	EuclidianPattern euclidianPattern_;
	EuclidianPattern euclidianAccentPattern_;
};

#endif
