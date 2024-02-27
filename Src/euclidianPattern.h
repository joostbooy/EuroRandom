#ifndef EuclidianPattern_h
#define EuclidianPattern_h

class EuclidianPattern {

public:

	static const size_t kMaxSteps = 16;

	void init() {
		update(kMaxSteps, kMaxSteps, 0);
		reset();
	}

	void reset() {
		trigger_pos_ = 0;
		duration_pos_ = 0;
	}

	void update(int steps, int pulses, int shifts) {
		steps_ = stmlib::clip(2, kMaxSteps - 1, steps);
		pulses_ = stmlib::clip(1, steps_, pulses);
		shifts_ = stmlib::clip(0, pulses_, shifts);

		int count = 0;
		int bucket = 0;
		int index = shifts_;

		triggers_ = 0;

		for (int i = 0; i < steps_; ++i) {
			++count;
			bucket += pulses_;

			if (bucket >= steps_) {
				bucket -= steps_;
				triggers_ |= 1 << ((i + shifts_) % steps_);
				duration_[index++ % pulses_] = count;
				count = 0;
			}
		}
	}

	bool next_trigger() {
		trigger_pos_ %= steps_;
		return triggers_ & (1 << trigger_pos_++);
	}

	uint8_t next_duration() {
		duration_pos_ %= pulses_;
		return duration_[duration_pos_++];
	}

private:
	int steps_;
	int shifts_;
	int pulses_;
	int duration_pos_;
	int trigger_pos_;
	int duration_[kMaxSteps];
	
	uint16_t triggers_;
};

#endif
