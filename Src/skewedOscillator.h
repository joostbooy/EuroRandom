#ifndef SkewedOscillator_h
#define SkewedOscillator_h

#include "pulse.h"
#include "oscillator.h"

class SkewedOscillator : public Oscillator {

public:

	void init() {
		stage_ = 0;
		value_ = 0.f;
		last_value_ = 0.f;
		target_value_ = 0.f;

		amount_ = 0.f;
		pulse_state_ = 0;
		pulse_.init();
		Oscillator::init();
	}

	void reset() {
		pulse_.init();
		Oscillator::reset();
	}

	void set_amount(float value) {
		amount_ = value;
	}

	void fill(uint16_t *data, const size_t inc, const size_t size) {
		for (size_t i = 0; i < size; ++i){
			*data = next_sample() * 65535;
			data += inc;
		}
	}

	void set_trigger_oscillator(bool state) {
		trigger_oscillator_ = state;
	}

	void manual_trigger() {
		pulse_.set(Oscillator::has_accent(), Oscillator::segment_duration());
	}

	bool pulse_state() {
		return pulse_state_;
	}

private:
	bool stage_;
	float amount_;
	float value_;
	float last_value_;
	float target_value_;

	Pulse pulse_;
	bool pulse_state_;
	bool trigger_oscillator_;

	inline float next_sample() {
		float phase_ = Oscillator::phase();
		float skew_ = skew(phase_, amount_);
		value_ = Dsp::cross_fade(last_value_, target_value_, skew_);

		pulse_state_ = pulse_.tick();

		if (Oscillator::tick() && trigger_oscillator_) {
			pulse_.set(Oscillator::has_accent(), Oscillator::segment_duration());
		}

		return value_;
	}

	inline float skew(float phase, float ammount) {
		if (phase < ammount) {
			set_stage(0);
			return phase * (1.0f / ammount);
		} else {
			set_stage(1);
			return (phase - ammount) * (1.0f / (1.0f - ammount));
		}
	}

	inline void set_stage(bool stage) {
		if (stage_ != stage) {
			stage_ = stage;
			last_value_ = value_;
			target_value_ = RandomGenerator::next(Oscillator::has_accent());
		}
	}
};

#endif
