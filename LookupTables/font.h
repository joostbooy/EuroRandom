#ifndef font_h
#define font_h

#include "stmf4lib.h"

class Font {

public:

	enum Type {
		SMALL,
		LARGE,
	};

	enum GlyphId {
		LOCK = 0x80,
		FILE,
		NOTE,
		ARROW_LEFT,
		ARROW_RIGHT,
		SWITCH_OFF,
		SWITCH_ON,
		CHECKMARK,
		CROSS,
		PLAY,
		METRONOME,
		PAUSE,
		STOP,
		FILLED_CIRCLE,
		CIRCLE,
		SINEWAVE,
		LABEL,
		SD_OK,
		NO_SD,
		ERROR,

		NUM_OF_GLYPHS
	};

	void set_type(Type);

	uint16_t height() {
		return height_;
	}

	uint16_t width(char c) {
		if (c >= first_char_ && c <= last_char_) {
			int width = *table_ptr(c);
			return width + 1;
		}
		return 0;
	}

	uint16_t string_width(const char* str) {
		uint16_t w = 0;
		while (*str != '\0') {
			w += width(*str++);
		}
		return w;
	}

	const uint8_t* data(char c) {
		return table_ptr(c) + 1;
	}

	const char* glyph(GlyphId id) {
		glyph_to_char_ = static_cast<const char>(id);
		return const_cast<const char*>(&glyph_to_char_);
	}

private:
	char first_char_;
	char last_char_;
	char glyph_to_char_;
	uint16_t height_;
	uint16_t table_width_;
	const uint8_t *data_;

	const uint8_t* table_ptr(char c) {
		int table_index = c - first_char_;
		return &data_[table_index * table_width_];
	}
};

extern Font font;

#endif
