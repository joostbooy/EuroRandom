#ifndef RandomGenerator_h
#define RandomGenerator_h

#include "stmf3lib.h"

class RandomGenerator {

public:

	static float read(bool accent) {
		if (u16() & 1) {
			return read_rising(kMin, accent);
		} else {
			return read_falling(kMax ,accent);
		}
	}

	static float read_rising(float min, bool accent) {
		if (accent) {
			return read(1.f - kAccentRange, 1.0f);
		} else {
			return read(clip(min), kMax);
		}
	}

	static float read_falling(float max, bool accent) {
		if (accent) {
			return read(0.f, kAccentRange);
		} else {
			return read(kMin, clip(max));
		}
	}

private:
	static constexpr float kAccentRange = 0.2f;
	static constexpr float kDeadBand = 0.05f;
	static constexpr float kMin = kAccentRange + kDeadBand;
	static constexpr float kMax = 1.f - (kAccentRange + kDeadBand);

	static inline float clip(float value) {
		if (value > kMax) {
			return kMax;
		} else if (value < kMin) {
			return kMin;
		}
		return value;
	}

	static inline float read(float min, float max) {
		return reciprocal() * (max - min) + min;
	}

	static uint16_t seed_;
	static uint16_t u16();
	static float reciprocal();
};

#endif
