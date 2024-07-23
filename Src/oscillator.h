#ifndef Oscillator_h
#define Oscillator_h

#include "dsp.h"
#include "randomGenerator.h"
#include "euclidianPattern.h"
#include "lookupTables.h"

class Oscillator {

public:

	void init() {
		inc_ = 0.1;
		phase_ = 0.f;
		accent_ = 0;
		duration_ = 1;
		segment_ticks_ = 500;

		euclidianPattern_.init();
		euclidianAccentPattern_.init();
	}

	void update_segments(float inc, uint32_t ticks, float fill, float accents, float shifts) {
		int pulses_ = fill * EuclidianPattern::kMaxSteps;
		int shifts_ = pulses_ * shifts;
		int accents_ = pulses_ * accents;

		euclidianPattern_.update(EuclidianPattern::kMaxSteps, pulses_, shifts);
		euclidianAccentPattern_.update(pulses_, accents_, shifts_);

		inc_ = inc;
		segment_ticks_ = ticks;
	}

	void reset() {
		phase_ = 0.f;
		euclidianPattern_.reset();
		euclidianAccentPattern_.reset();
	}

	uint32_t segment_duration() {
		return segment_ticks_ * duration_;
	}

	float phase() {
		return phase_;
	}

	bool has_accent() {
		return accent_;
	}

	bool tick() {
		phase_ += inc_ * lut_reciprocal[duration_];

		if (phase_ >= 1.f)  {
			phase_ = 0.f;
			accent_ = euclidianAccentPattern_.next_trigger();
			duration_ = euclidianPattern_.next_duration();
			return true;
		}

		return false;
	}

private:
	float inc_;
	float phase_;
	bool accent_;
	uint8_t duration_;
	uint32_t segment_ticks_;
	EuclidianPattern euclidianPattern_;
	EuclidianPattern euclidianAccentPattern_;
};

#endif
