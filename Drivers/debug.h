#ifndef debug_h
#define debug_h

#include "stm32f4xx.h"

class Debug {

public:
    void init();

	inline bool read() {
		return GPIOB->IDR & GPIO_PIN_7;
	}

	inline void write(bool state) {
        GPIOB->BSRR = state ? GPIO_PIN_6 : GPIO_PIN_6 << 16;
    }

    inline void toggle() {
		(toggle_state ^= 1) ? write(1) : write(0);
    }

private:
	uint8_t toggle_state = 0;
};

#endif
