#ifndef Gate_h
#define Gate_h

#include "randomGenerator.h"

class Gate {

public:

	void init() {
		duration_ = 0;
	}

	void set(bool accent, uint32_t duration) {
		duration_ = duration * RandomGenerator::next(accent);
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
