#ifndef Dac_h
#define Dac_h

#include "stm32f4xx.h"
#include "debug.h"

class Dac {

public:

	struct Buffer {
		uint16_t channel[4];
	};

	static Dac *dac_;

	static constexpr size_t update_rate() {
		return kSamplerate / kBlockSize / kNumChannels;
	}

	void init();
	void start(void(*callback)(Buffer*, size_t));

	void fill(const size_t offset) {
		callback_(buffer_, kBlockSize);

		uint16_t *ptr = reinterpret_cast<uint16_t*>(&dma_buffer_[offset * (kDmaBufferSize / 2)]);

		for (size_t i = 0; i < kBlockSize; ++i) {
			for (size_t chn = 0; chn < kNumChannels; ++chn) {
				uint16_t sample = buffer_[i].channel[chn];
				*ptr++ = 0x1000 | (chn << 9) | (sample >> 8);
				*ptr++ = sample << 8;
			}
		}
	}

private:
	static const size_t kSamplerate = 64285;
	static const size_t kBlockSize = 16;
	static const size_t kNumChannels = 4;
	static const uint32_t kDmaBufferSize = kBlockSize * kNumChannels * 2;

	Buffer buffer_[kBlockSize];
	uint32_t dma_buffer_[kDmaBufferSize];

	typedef void(*Callback)(Buffer*, size_t);
	Callback callback_;
};

#endif
