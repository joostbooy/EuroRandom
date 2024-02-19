#ifndef GateIo_h
#define GateIo_h

#include "stmf3lib.h"

class GateIo {

public:

	void init();


	// Inputs
	bool read_clock() {
		return !(GPIOC->IDR & GPIO_PIN_13);
	}

	bool read_trigger() {
		return !(GPIOC->IDR & GPIO_PIN_15);
	}

	bool read_reset() {
		return !(GPIOB->IDR & GPIO_PIN_14);
	}

	bool read_burst() {
		return !(GPIOB->IDR & GPIO_PIN_8);
	}

	// insert detection
	bool read_burst_insert() {
		return GPIOB->IDR & GPIO_PIN_5;
	}

	bool read_trigger_insert() {
		return GPIOC->IDR & GPIO_PIN_14;
	}

	// Outputs
	void write_pulse(bool state) {
		GPIOA->BSRR = state ? GPIO_PIN_3 : GPIO_PIN_3 << 16;
	}

	void write_gate(bool state) {
		GPIOA->BSRR = state ? GPIO_PIN_4 : GPIO_PIN_4 << 16;
	}

	void write_burst(bool state) {
		GPIOA->BSRR = state ? GPIO_PIN_5 : GPIO_PIN_5 << 16;
	}

	void write_noise(bool state) {
		GPIOA->BSRR = state ? GPIO_PIN_7 : GPIO_PIN_7 << 16;
	}

	void write_clock_led(bool state) {
		GPIOB->BSRR = state ? GPIO_PIN_9 : GPIO_PIN_9 << 16;
	}

private:

};

extern GateIo gateIo;

#endif
