#ifndef FrameBuffer_h
#define FrameBuffer_h

#include "stmf4lib.h"

// 4 bit grayscale buffer

template <const uint16_t kWidth, const uint16_t kHeight>
class FrameBuffer {

public:

	inline bool inside(int x, int y) {
		return (x >= 0 && x < kWidth) && (y >= 0 && y < kHeight);
	}

	inline void clear() {
		int i = size_;
		while (i--) {
			data_[i] = 0x00;
		}
	}

	inline void write(int x, int y, uint8_t value) {
		int index = (x / 2) + ((kWidth / 2) * y);

		if (x & 1) {
			data_[index] &= ~0x0F;
			data_[index] |= (value & 0x0F);
		} else {
			data_[index] &= ~0xF0;
			data_[index] |= (value << 4);
		}
	}

	inline uint8_t read(int x, int y) {
		int index = (x / 2) + ((kWidth / 2) * y);

		if (x & 1) {
			return data_[index] & 0x0F;
		} else {
			return (data_[index] & 0xF0) >> 4;
		}
	}

	const int size() { return size_; }
	uint8_t *data() { return data_; }

private:
	static const int size_ = (kWidth * kHeight) / 2;
	uint8_t data_[size_];
};


#endif
