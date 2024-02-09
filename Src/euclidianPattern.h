#ifndef EuclidianPattern_h
#define EuclidianPattern_h

class EuclidianPattern {

public:

	void init() {
		update(32, 32, 0);
		reset();
	}

	void reset() {
		position_ = 0;
	}
	
	void update(int steps, int pulses, int shifts) {
		steps_ = stmlib::clip(2, kMaxSteps - 1, steps);
		pulses_ = stmlib::clip(1, steps_, pulses);
		shifts_ = stmlib::clip(0, pulses_, shifts);

		int count = 0;
		int bucket = 0;
		int index = shifts_;

		for (int i = 0; i < steps_; ++i) {
			++count;
			bucket += pulses_;

			if (bucket >= steps_) {
				bucket -= steps_;
				duration_[++index % pulses_] = count;
				count = 0;
			}
		}
	}

	int next_duration() {
		position_ %= pulses_;
		return duration_[position_++];
	}

private:
	static const size_t kMaxSteps = 32;

	int steps_;
	int shifts_;
	int pulses_;
	int position_;
	int duration_[kMaxSteps];
};

#endif
