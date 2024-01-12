#ifndef Micros_h
#define Micros_h

#include "stmf4lib.h"

class Micros {

public:
	void init();

	inline volatile uint32_t read() {
		return TIM5->CNT;
	}

	void delay(uint32_t us) {
		uint32_t start = read();
		while (static_cast<uint32_t>(read() - start) < us);
	}

private:

};

extern Micros micros;

#endif
