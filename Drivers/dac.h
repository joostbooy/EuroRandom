#ifndef Dac_h
#define Dac_h

#include "stmf3lib.h"
#include "micros.h"

class Dac {

public:

	void init(uint16_t* (*callback)(size_t));

	void fill(int offset) {
		uint16_t* sample_buffer = callback_(kBufferSize);
		uint32_t* dma_buffer = &dma_buffer_[offset * kBufferSize];

		for (size_t i = 0; i < kBlockSize; ++i) {
			for (size_t channel = 0; channel < kNumChannels; ++channel) {
				uint16_t sample = sample_buffer[(channel * kBlockSize) + i];
				*dma_buffer++ = (1 << 28) | (channel << 25) | (sample << 8);
			}
		}
	}

private:
	static const size_t kBlockSize = 16;
	static const size_t kNumChannels = 4;
	static const size_t kBufferSize = kBlockSize * kNumChannels;

	uint32_t dma_buffer_[2 * kBufferSize];

	typedef uint16_t* (*Callback)(size_t);
	Callback callback_;
};

extern Dac dac;

#endif
