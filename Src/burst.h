#ifndef Burst_h
#define Burst_h

#include "randomGenerator.h"

class Burst {

public:

	void init() {
		duration_ = 0;
	}

	void reset(bool accent, uint32_t duration) {

	}

	bool tick() {
		if (duration_ > 0) {
			--duration;
			return true;
		}
		return false;
	}

private:
	int duration_;
};

#endif
