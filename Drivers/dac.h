#ifndef Dac_h
#define Dac_h

#include "stmf3lib.h"

class Dac {

public:

	struct Buffer {
		uint16_t channel[4];
	};

	static Dac *dac_;

	static constexpr size_t update_rate() {
		return kSamplerate / kBlockSize;
	}

	void init();
	void start(void(*callback)(Buffer*, size_t));

	void fill(const size_t offset) {
		callback_(buffer_, kBlockSize);

		uint32_t *ptr = &dma_buffer_[offset * (kDmaBufferSize / 2)];

		for (size_t i = 0; i < kBlockSize; ++i) {
			for (size_t chn = 0; chn < kNumChannels; ++chn) {
				*ptr++ = (1 << 28) | (chn << 25) | (buffer_[i].channel[chn] << 8);	// << 10 maybe?
			}
		}
	}

private:
	// SampleRate	Real	UpdateRate (16 / 8 block)	Latency mS
	// 32000		32142	2008 / 4017					0.49 / 0.24
	// 22000		22058	1378 / 2757					0.72 / 0.36
	// 16000		15957	997 / 1994					1.0 / 0.5
	// 11000		10975	685 / 1371					1.4 / 0.72

	static const size_t kSamplerate = 15957;
	static const size_t kBlockSize = 16;
	static const size_t kNumChannels = 4;
	static const size_t kDmaBufferSize = kBlockSize * kNumChannels * 2;

	Buffer buffer_[kBlockSize];
	uint32_t dma_buffer_[kDmaBufferSize];

	typedef void(*Callback)(Buffer*, size_t);
	Callback callback_;
};

#endif
