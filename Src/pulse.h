#ifndef Pulse_h
#define Pulse_h

#include "randomGenerator.h"

class Pulse {

public:

	void init() {
		duration_ = 0;
	}

	void set(bool accent, uint32_t duration) {
		if (accent || RandomGenerator::next_bool()) {
			duration_ = duration >= 4 ? (duration / 4) : 1;
		}
	}

	bool tick() {
		if (duration_ > 0) {
			--duration_;
			return true;
		}
		return false;
	}

private:
	int duration_;
};

#endif
