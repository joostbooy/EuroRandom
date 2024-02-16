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
	}

	void tick(bool state) {
		last_state_ = curr_state_;
		curr_state_ = state;

		if (curr_state_ == 1 && last_state_ == 0) {
			uint32_t new_interval_ = curr_tick - last_tick_;
			if (new_interval_ >= 8 && new_interval_ <= 2000) {
				interval_ = new_interval_;
			}
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
};

#endif
