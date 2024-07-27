#ifndef adc_h
#define adc_h

#include "stm32f4xx.h"


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
		if (++channel_ >= kNumChannels) {
			channel_ = 0;
		}

		if (channel_ < kNumMuxChannels) {
			set_mux_channel(channel_);
			ADC1->SQR3 = ADC_CHANNEL_8;
		} else if (channel_ == 8) {
			ADC1->SQR3 = ADC_CHANNEL_2;
		} else {
			ADC1->SQR3 = ADC_CHANNEL_6;
		}

		ADC1->CR2 |= ADC_CR2_SWSTART;
	}

private:
	static const int kNumMuxChannels = 8;
	static const int kNumChannels = 10;
	uint8_t channel_ = 0;

	void set_mux_channel(uint8_t channel) {
		uint32_t reg = 0;
		channel & 0x01 ? reg |= GPIO_PIN_1 : reg |= GPIO_PIN_1 << 16;
		channel & 0x02 ? reg |= GPIO_PIN_2 : reg |= GPIO_PIN_2 << 16;
		channel & 0x04 ? reg |= GPIO_PIN_10 : reg |= GPIO_PIN_10 << 16;
		GPIOB->BSRR = reg;
	}
};

#endif
