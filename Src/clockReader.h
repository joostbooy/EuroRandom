#ifndef ClockReader_h
#define ClockReader_h

#include "micros.h"

class ClockReader {

public:

	void init() {
		curr_tick = 0;

		curr_state_ = 0;
		last_state_ = 0;
		last_tick_ = 0;
		interval_ = 48000;
	}

	uint32_t read() {
		last_state_ = curr_state_;
		curr_state_ = debounce(gateIo.read_clock());

		if (curr_state_ == 1 && last_state_ == 0) {
			interval_ = curr_tick - last_tick_;
			last_tick_ = curr_tick;
		}

		++curr_tick;
		return interval_;
	}

private:
	bool last_state_;
	bool curr_state_;

	uint32_t interval_;
	uint32_t last_tick_;
	uint32_t curr_tick = 0;

	uint8_t prescaler = 0;
	uint8_t debouncer = 0;

	inline bool debounce(bool state) {
		if ((++prescaler & 15) == 0) {
			debouncer <<= 1;
			if (state) {
				debouncer |= 1;
			}
		}
		return debouncer == 0xFE;
	}

};

#endif
