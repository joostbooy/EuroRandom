#include "canvas.h"

Canvas canvas;

void Canvas::draw_bitmap(int x, int y, Bitmap::Id id, int frame) {
	set_bitmap(id);

	int shift = 0;
	int x2 = x + bitmap.width;
	int y2 = y + bitmap.height;
	const uint8_t* ptr = bitmap.pointer(frame);

	for (int xi = x; xi < x2; ++xi) {
		for (int yi = y; yi < y2; ++yi) {
			uint8_t pixel = (*ptr >> shift) & 1;
			draw_pixel(xi, yi, pixel ? BLACK : WHITE);
			if (++shift >= 8) {
				++ptr;
				shift = 0;
			}
		}

		if(shift != 0) {
			++ptr;
			shift = 0;
		}
	}
}

void Canvas::draw_char(int x, int y, char c) {
	const uint8_t* ptr = font.data(c);
	int char_width = font.width(c);
	text_cursor_ = x;

	for (int i = 0; i < char_width; ++i) {
		uint8_t data = *ptr++;
		for (int pixel = 0; pixel < font.height(); ++pixel) {
			if (data & (1 << pixel)) {
				draw_pixel(text_cursor_, y + pixel, font_color);
			}
		}
		++text_cursor_;
	}
}
