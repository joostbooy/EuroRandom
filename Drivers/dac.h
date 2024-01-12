#ifndef Dac_h
#define Dac_h

#include "stmf4lib.h"
#include "micros.h"

// https://github.com/westlicht/performer/blob/master/src/platform/stm32/drivers/Dac.h
// https://github.com/westlicht/performer/blob/master/src/platform/stm32/drivers/Dac.cpp
// https://github.com/westlicht/performer/blob/master/src/platform/stm32/hal/Delay.h

#define WRITE_INPUT_REGISTER            0
#define UPDATE_OUTPUT_REGISTER          1
#define WRITE_INPUT_REGISTER_UPDATE_ALL 2
#define WRITE_INPUT_REGISTER_UPDATE_N   3
#define POWER_DOWN_UP_DAC               4
#define LOAD_CLEAR_CODE_REGISTER        5
#define LOAD_LDAC_REGISTER              6
#define RESET_POWER_ON                  7
#define SETUP_INTERNAL_REF              8

class Dac {

public:

	enum ClearCode {
		ClearZeroScale  = 0,
		ClearMidScale   = 1,
		ClearFullScale  = 2,
		ClearIgnore     = 3,
	};

	void init();

	uint16_t value(uint8_t channel) {
		return value_[channel];
	}

	void set(uint8_t channel, uint16_t value) {
		value_[channel] = value;
	}

	void write(int channel) {
		writeDac(WRITE_INPUT_REGISTER_UPDATE_N, channel, value_[channel], 15);
	}

	void write() {
		for (int i = 0; i < kNumChannels; ++i) {
			writeDac(i == 7 ? WRITE_INPUT_REGISTER_UPDATE_ALL : WRITE_INPUT_REGISTER, i, value_[i], 0);
		}
	}

private:
	static const int kNumChannels = 8;
	uint16_t value_[kNumChannels];
	volatile uint8_t dummy;

	void writeDac(uint8_t command, uint8_t address, uint16_t data, uint8_t function) {
		uint8_t b1 = command;
		uint8_t b2 = (address << 4) | (data >> 12);
		uint8_t b3 = data >> 4;
		uint8_t b4 = (data & 0xf) << 4 | function;

		// sync_pin LOW
		GPIOA->BSRR = GPIO_PIN_4 << 16;
		asm("NOP");

		spi_write(b1);
		spi_write(b2);
		spi_write(b3);
		spi_write(b4);
		asm("NOP");

		// sync_pin HIGH
		GPIOA->BSRR = GPIO_PIN_4;
		asm("NOP");
	}

	void reset() {
		writeDac(RESET_POWER_ON, 0, 0, 0);
		micros.delay(50);
	}

	void setInternalRef(bool enabled) {
		writeDac(SETUP_INTERNAL_REF, 0, 0, enabled ? 1 : 0);
	}

	void setClearCode(ClearCode code) {
		writeDac(LOAD_CLEAR_CODE_REGISTER, 0, 0, code);
	}

	void spi_write(uint8_t data) {
		while (!(SPI1->SR & SPI_FLAG_TXE));
		SPI1->DR = data;

		while (!(SPI1->SR & SPI_FLAG_RXNE));
		dummy = SPI1->DR;
	}

};

extern Dac dac;

#endif
