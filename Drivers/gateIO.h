#ifndef GateOut_h
#define GateOut_h

#include "stmf4lib.h"

class GateIO {

public:
	void init();

	bool read_input(uint8_t channel) {
		switch (channel)
		{
		case 0: return !(GPIOB->IDR & GPIO_PIN_14);
		case 1: return !(GPIOB->IDR & GPIO_PIN_11);
		case 2: return !(GPIOB->IDR & GPIO_PIN_10);
		case 3: return !(GPIOE->IDR & GPIO_PIN_15);
		default:
			break;
		}
		return 0;
	}

	void set_output(uint8_t channel, bool state) {
		uint8_t bits = out_bits_;
		uint8_t mask = (1 << channel);

		if (state == 1) {
			out_bits_ = bits | mask;
		} else {
			out_bits_ = bits & ~mask;
		}
	}

	void write_output() {
		// select
		//GPIOE->BSRR = GPIO_PIN_11 << 16;

		// write
		while (!(SPI4->SR & SPI_FLAG_TXE));
		SPI4->DR = out_bits_;

		while (!(SPI4->SR & SPI_FLAG_RXNE));
		dummy = SPI4->DR;

		// latch
		GPIOE->BSRR = GPIO_PIN_11 << 16;
		GPIOE->BSRR = GPIO_PIN_11;
	}

	bool read_output(uint8_t channel) {
		return out_bits_ & (1 << channel);
	}

private:
	uint8_t out_bits_;
	volatile uint8_t dummy;
};

extern GateIO gateIO;

#endif
