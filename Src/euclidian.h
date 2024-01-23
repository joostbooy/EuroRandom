#ifndef EuclidianPattern_h
#define EuclidianPattern_h

class EuclidianPattern {

public:

	void init() {
		update(32, 32);
		reset();
	}

	void reset() {
		position_ = 0;
	}

	void update(int steps, int pulses) {
		steps_ = stmlib::clip(2, kMaxSteps - 1, steps);
		pulses_ = stmlib::clip(1, steps_, pulses);
		
		// pattern
		int bucket = 0;
		uint32_t bits = 0;

		for (int i = 0; i < steps_; ++i) {
			bucket += pulses_;
			if (bucket >= steps_) {
				bucket -= steps_;
				bits |= (1 << i);
			}
		}

		// duration
		int ticks = 0;
		int index = pulses_ - 1;

		for (int i = 0; i < steps_; ++i) {
			++ticks;
			if (bits & (1 << i)) {
				duration_[index--] = ticks;
				ticks = 0;
			}
		}
	}

	int next_duration() {
		int value = duration_[position_];

		++position_;
		if (position_ >= pulses_) {
			position_ = 0;
		}

		return value;
	}

private:
	static const size_t kMaxSteps = 32;

	int steps_;
	int pulses_;
	int position_;
	int duration_[kMaxSteps];
};

#endif
