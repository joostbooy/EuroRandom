#ifndef Noise_h
#define Noise_h

#include "randomGenerator.h"

class Noise {

public:

	void init() {
		reset(false, 0);
	}

	void reset(bool accent, uint32_t duration) {
		duration_ = 0;
		total_ = duration_;
		min_ = accent ? 0.05f : 0.5f;
	}

	bool tick() {
		if (duration_ == 0 && total_ > 0) {
			duration_ = RandomGenerator::falling(min_) * total_;
			total_ -= duration_;
		}

		if (duration_ > 0) {
			--duration;
			return true;
		}
		return false;
	}

private:
	int duration_;
	int total_;
	float min_;
};

#endif
