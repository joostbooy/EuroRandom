#ifndef ClockReader_h
#define ClockReader_h

class ClockReader {

public:

	void init() {
		curr_tick = 0;

		curr_state_ = 0;
		last_state_ = 0;
		last_tick_ = 0;
		interval_ = 100;

		count_ = 0;
		average_ = 0;
	}

	void tick(bool state) {
		last_state_ = curr_state_;
		curr_state_ = state;

		if (curr_state_ == 1 && last_state_ == 0) {
			interval_ = stmlib::clip(8, 2000, curr_tick - last_tick_);
			last_tick_ = curr_tick;

		}
		++curr_tick;
	}

	uint32_t interval() {
		return interval_;
	}

private:
	bool last_state_;
	bool curr_state_;

	uint32_t interval_;
	uint32_t last_tick_;
	uint32_t curr_tick;

	uint8_t count_;
	uint32_t average_;

	inline void average(uint32_t value) {
		average_ += value;
		if ((++count_ % 4) == 3) {
			interval_ = average_ / 4;
			average_ = 0;
		}
	}
};

#endif
