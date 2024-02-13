#ifndef Oscillator_h
#define Oscillator_h

#include "dsp.h"
#include "euclidianPattern.h"


class Oscillator {

public:

	void init() {
		inc_ = 0.1;
		phase_ = 0.f;
		euclidianPattern_.init();
	}

	//Gate &gate() {
	//	return gate_;
	//}

	EuclidianPattern &euclidianPattern() {
		return euclidianPattern_;
	}

	void reset() {
		phase_ = 0.f;
		euclidianPattern_.reset();
	}

	uint32_t segment_ticks() {
		return segment_ticks_;
	}

	void set_segment_ticks(uint32_t value) {
		segment_ticks_ = value;
	}

	float phase() {
		return phase_;
	}

	bool tick() {
		phase_ += inc_;
		if (phase_ >= 1.f)  {
			phase_ = 0.f;
			inc_ = segment_ticks_ / euclidianPattern_.next_duration();
			return true;
		}
		return false;
	}

private:
	float inc_;
	float phase_;

	uint32_t segment_ticks_;
	EuclidianPattern euclidianPattern_;
};

#endif
