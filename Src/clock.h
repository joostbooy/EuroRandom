#ifndef Clock_h
#define Clock_h

class Clock {

public:

	void update() {
		for (int i = 0; i < kNumClocks; ++i) {
			bool state = read(i);

			if (state == 1 && last_state_[i] == 0) {
				last_state_[i] = state;
				interval_[i] = curr_tick - last_update_[i];
				last_update_[i] = mircos.read();
			}
		}
	}

	uint32_t interval(int port) {
		return interval_[port];
	}

private:

	static const size_t kNumClocks = 2;
	bool last_state_[kNumClocks];
	uint32_t interval_[kNumClocks];
	uint32_t last_update_[kNumClocks];

	inline bool read(int port) {
		if (port == 0) {
			return !(GPIOA->BSRR & GPIO_PIN_7);
		} else {
			return !(GPIOA->BSRR & GPIO_PIN_4);
		}
	}
};

#endif
