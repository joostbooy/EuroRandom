#ifndef RandomGenerator_h
#define RandomGenerator_h

#include "stmf3lib.h"

class RandomGenerator {

public:

	static float next(bool accent) {
		if (state_ & 1) {
			return next_rising(kMin, accent);
		} else {
			return next_falling(kMax, accent);
		}
	}

	static float next_falling(float max, bool accent) {
		if (accent) {
			return read(0.f, kAccentRange);
		} else {
			return read(kMin, clip(max));
		}
	}

	static float next_rising(float min, bool accent) {
		if (accent) {
			return read(1.f - kAccentRange, 1.0f);
		} else {
			return read(clip(min), kMax);
		}
	}

	static bool next_bool() {
		return u16() & 1;
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

	static uint16_t state_;

	static inline uint16_t u16() {
		state_ = state_ * 1664525L + 1013904223L;
		return state_;
	}

	static inline float read(float min, float max) {
		return (1.f / 65535.f) * u16() * (max - min) + min;
	}
};

#endif
