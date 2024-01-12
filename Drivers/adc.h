#ifndef adc_h
#define adc_h

#include "stmf4lib.h"


class Adc {

public:
	void init();

	inline bool ready() {
		return ADC1->SR & ADC_SR_EOC;
	}

	// circuit is inverted
	inline uint16_t read() {
		return 4095 - ADC1->DR;
	}

	inline uint8_t curr_channel(){
		return channel;
	}

	inline void convert_next_channel() {
		switch (++channel &= 3)
		{
		case 0:	ADC1->SQR3 = ADC_CHANNEL_8;
			break;
		case 1:	ADC1->SQR3 = ADC_CHANNEL_9;
			break;
		case 2:	ADC1->SQR3 = ADC_CHANNEL_14;
			break;
		case 3:	ADC1->SQR3 = ADC_CHANNEL_15;
			break;
		default:
			break;
		}
		ADC1->CR2 |= ADC_CR2_SWSTART;
	}

private:
	uint8_t channel = 0;
};

extern Adc adc;

#endif
