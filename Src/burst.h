#ifndef Burst_h
#define Burst_h

#include "randomGenerator.h"

class Burst {

public:

	void init() {

	}

	void reset(bool accent, uint32_t duration) {
		phase_ = 0.f;
		inc_ = accent ? (1.f / 64.f) : (1.f / 32.f);

		duration_ = 0;
		total_used_ = 0;
		total_ = duration;
	}

	bool tick() {
		while (duration_ == 0 && phase_ < 1.f) {
			duration_ = next_duration();
		}

		if (duration_ > 0) {
			--duration_;
			return true;
		}
		return false;
	}

private:
	uint32_t total_;
	uint32_t total_used_;
	uint32_t duration_;

	float inc_;
	float phase_;

	uint32_t next_duration() {
		uint32_t next;

		phase_ += inc_;
		next = total_ * (phase_ * phase_) * RandomGenerator::next(1.f - inc_, 1.f, false);
		next -= total_used_;
		total_used_ += next;

		return next;
	}

};

#endif
