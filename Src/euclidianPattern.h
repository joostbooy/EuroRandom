#ifndef EuclidianPattern_h
#define EuclidianPattern_h

class EuclidianPattern {

public:

	void init() {
		update(32, 32, 0);
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
				duration_[++index %= pulses_] = count;
				count = 0;

				triggers_ |= (1 << i);
			}
		}

		triggers_ = shift_triggers(triggers_, shifts_);
	}

	bool next_trigger() {
		trigger_pos_ %= steps_;
		return triggers_ & (1 << trigger_pos_++);
	}

	int next_duration() {
		duration_pos_ %= pulses_;
		return duration_[duration_pos_++];
	}

private:
	static const size_t kMaxSteps = 32;

	int steps_;
	int shifts_;
	int pulses_;
	int duration_pos_;
	int trigger_pos_;
	int duration_[kMaxSteps];

	uint32_t triggers_;

	uint32_t shift_triggers(uint32_t data, int shifts) {
		return (data >> shifts) | (data << (31 - shifts));
	}
};

#endif
