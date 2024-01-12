#ifndef debug_h
#define debug_h

#include "stmf4lib.h"

class Debug {

public:
    void init();

	inline bool read() {
		return GPIOE->IDR & GPIO_PIN_0;
	}

	inline void write(bool state) {
        GPIOE->BSRR = state ? GPIO_PIN_1 : GPIO_PIN_1 << 16;
    }

    inline void toggle() {
		(toggle_state ^= 1) ? write(1) : write(0);
    }

private:
	uint8_t toggle_state = 0;
};

extern Debug debug;

#endif
