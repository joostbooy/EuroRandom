#ifndef Noise_h
#define Noise_h

#include "randomGenerator.h"

class Noise {

public:

	void init() {
		reset(false, 0);
	}

	void set(bool accent, uint32_t duration) {
		duration_ = 0;
		total_ = duration_;
		max_ = accent ? 0.05f : 0.5f;
	}

	bool tick() {
		if (duration_ == 0 && total_ > 0) {
			duration_ = RandomGenerator::falling(max_) * total_;
			total_ -= duration_;

			width_ = duration_;
			width_ -= duration_ >= 4 ? (duration_ / 4) : 1;
		}

		if (duration_ > 0) {
			--duration;
			return duration_ >= width_;
		}

		return false;
	}

private:
	int duration_;
	int total_;
	int width_;
	float max_;
};

#endif
