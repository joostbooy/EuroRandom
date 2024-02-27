#ifndef Clock_h
#define Clock_h

#include "dac.h"

class Clock {

public:

	void init() {
		curr_tick = 0;
		curr_state_ = 0;
		last_state_ = 0;
		last_tick_ = 0;
		set_interval(500);
		reset();
	}

	void reset() {
		phase_ = 0.f;
		external_phase_ = 0.f;
	}

	void tick(bool state) {
		last_state_ = curr_state_;
		curr_state_ = state;

		if (curr_state_ == 1 && last_state_ == 0) {
			uint32_t new_interval_ = curr_tick - last_tick_;
			if (new_interval_ >= kMinInterval && new_interval_ <= kMaxInterval) {
				set_interval(new_interval_);
			}
			last_tick_ = curr_tick;
		}
		++curr_tick;

		sync();
	}

	uint32_t interval() {
		return interval_;
	}

	float inc() {
		return inc_;
	}

	float phase() {
		return phase_;
	}

private:
	bool last_state_;
	bool curr_state_;

	uint32_t interval_;
	uint32_t last_tick_;
	uint32_t curr_tick;

	float inc_;
	float phase_;
	float external_inc_;
	float external_phase_;

	static const uint32_t kMinInterval = (Dac::update_rate() / 1000.f) * 8.f;
	static const uint32_t kMaxInterval = (Dac::update_rate() / 1000.f) * 2500.f;

	void set_interval(uint32_t value) {
		interval_ = value;
		external_inc_ = 1.f / value;
		external_phase_ = 0.f;
	}

	void sync() {
		external_phase_ += external_inc_;
		if (external_phase_ >= 1.0f) {
			external_phase_ = 0.f;
		}

		phase_ += inc_;
		if (phase_ >= 1.0f) {
			phase_ = 0.f;
		}

		float phase_diff = external_phase_ - phase_;
		inc_ = external_inc_ + (phase_diff * 0.05f);
	}

};

#endif
