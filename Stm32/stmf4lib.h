#ifndef STM32F4Lib_h
#define STM32F4Lib_h

#include "stm32f4xx.h"
#include <functional>
#include <stdlib.h>
#include <stdint.h>
#include <limits>
#include <cstring>
#include <cmath>

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

	template<typename type>
	static inline float int_to_float(type value) {
		return (1.0f / abs(std::numeric_limits<type>::min())) * value;
	}

	template<typename type>
	static inline type float_to_int(float value) {
		const type min = std::numeric_limits<type>::min();
		const type max = std::numeric_limits<type>::max();
		return clip(min, max, value * abs(min));
	}

	template<typename type>
	static inline float uint_to_float(type value) {
		return (1.0f / std::numeric_limits<type>::max()) * value;
	}

	template<typename type>
	static inline type float_to_uint(float value) {
		const type max = std::numeric_limits<type>::max();
		return clip(0, max, value * max);
	}
};

#endif
