#ifndef Clock_h
#define Clock_h

#include "micros.h"

class Clock {

public:

	void init() {
		curr_tick = 0;

		for (size_t i = 0; i < kNumClocks; ++i) {
			curr_state_[i] = 0;
			last_state_[i] = 0;
			interval_[i] = 0;
			last_tick_[i] = 0;
		}
	}

	void poll() {
		for (size_t i = 0; i < kNumClocks; ++i) {
			last_state_[i] = curr_state_[i];
			curr_state_[i] = read(i);

			if (curr_state_[i] == 1 && last_state_[i] == 0) {
				interval_[i] = curr_tick - last_tick_[i];
				last_tick_[i] = curr_tick;
			}
		}

		++curr_tick;
	}

	uint32_t interval(int port) {
		return interval_[port];
	}

	bool current_state(int port) {
		return curr_state_[port];
	}

private:

	static const size_t kNumClocks = 2;

	bool last_state_[kNumClocks];
	bool curr_state_[kNumClocks];

	uint32_t interval_[kNumClocks];
	uint32_t last_tick_[kNumClocks];
	uint32_t curr_tick = 0;

	inline bool read(int port) {
		switch (port)
		{
		case 0:	return !(GPIOA->BSRR & GPIO_PIN_7);
		case 1:	return !(GPIOA->BSRR & GPIO_PIN_4);
		default:
			break;
		}
		return 0;
	}

};
inline float curve(float shape) {
	uint16_t intergral = static_cast<uint16_t>(phase_);
	float fractional = phase_ - intergral;

	const float *lut_a = &lut_exp[intergral];
	const float *lut_b = &lut_inv_exp[intergral];
	float a = Dsp::cross_fade(*lut_a, *(lut_a + 1), fractional);
	float b = Dsp::cross_fade(*lut_b, *(lut_b + 1), fractional);

	return Dsp::cross_fade(a, b, shape);
}

#endif
