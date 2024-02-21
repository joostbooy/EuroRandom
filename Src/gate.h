#ifndef Gate_h
#define Gate_h

#include "randomGenerator.h"

class Gate {

public:

	void init() {
		duration_ = 0;
	}

	void set(bool accent, uint32_t duration) {
		if (accent) {
			duration_ = duration > 1 ? duration - 1 : 1;
		} else {
			duration_ = duration * RandomGenerator::next(0.0f, 0.65f);
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
