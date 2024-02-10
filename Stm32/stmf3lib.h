#ifndef STM32F3LIB_h
#define STM32F3LIB_h

#include "stm32f3xx.h"

//#include <cstddef>
//#include <stdlib.h>
//#include <stdint.h>
//#include <cstring>
//#include <cmath>

//#include <functional>
//#include <assert.h>
//#include <algorithm>

#define CCM_RAM __attribute__((section(".ccmram")))
#define FORCE_INLINE __attribute__((always_inline))

class stmlib {

public:

	static inline int clip_min(int min, int value) {
		return value > min ? value : min;
	}

	static inline int clip_max(int max, int value) {
		return value < max ? value : max;
	}

	static inline int clip(int min, int max, int value) {
		return value > max ? max : (value < min ? min : value);
	}

	template <typename type>
	static inline type difference(type a, type b) {
		return a > b ? a - b : b - a;
	}

	template <typename type>
	static inline void swap(type &a,type &b) {
		type temp = a;
		a = b;
		b = temp;
	}
};

#endif
