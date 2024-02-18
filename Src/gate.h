#ifndef Gate_h
#define Gate_h

#include "randomGenerator.h"

class Gate {

public:

	void init() {
		duration_ = 0;
	}

	void reset(bool accent, uint32_t duration) {
		if (accent) {
			duration_ = duration > 1 ? duration - 1 : 1;
		} else {
			duration_ = duration * RandomGenerator::next_falling(0.65f, false);
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
