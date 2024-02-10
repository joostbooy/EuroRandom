#ifndef adc_h
#define adc_h

#include "stmf4lib.h"


class Adc {

public:
	void init();

	inline bool ready() {
		return ADC1->SR & ADC_SR_EOC;
	}

	inline uint16_t read() {
		return ADC1->DR;
	}

	inline uint8_t curr_channel(){
		return channel_;
	}

	inline void convert_next_channel() {
		// set channel
		if (++channel_ >= kNumChannels) {
			channel_ = 0;
		}

		uint32_t reg = 0;

		if (channel_ < kNumMuxChannels) {
			channel_ & 0x01 ? reg |= GPIO_PIN_1 : reg |= GPIO_PIN_1 << 16;
			channel_ & 0x02 ? reg |= GPIO_PIN_2 : reg |= GPIO_PIN_2 << 16;
			channel_ & 0x04 ? reg |= GPIO_PIN_10 : reg |= GPIO_PIN_10 << 16;
			GPIOB->BSRR = reg;

			ADC1->SQR3 = ADC_CHANNEL_11;
		} else if (channel_ == 8) {
			ADC1->SQR3 = ADC_CHANNEL_3;
		} else {
			ADC1->SQR3 = ADC_CHANNEL_10;
		}

		// start converion
		ADC1->CR2 |= ADC_CR2_SWSTART;
	}

private:
	static const int kNumMuxChannels = 8;
	static const int kNumChannels = 10;
	uint8_t channel_ = 0;
};

extern Adc adc;

#endif
