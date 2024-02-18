#ifndef Pulse_h
#define Pulse_h

#include "randomGenerator.h"

class Pulse {

public:

	void init() {
		duration_ = 0;
	}

	void reset(bool accent) {
		if (accent || RandomGenerator::next_bool()) {
			duration_ = (Dac::kUpdateRate / 1000) * 5;	// 5 ms
		}
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
