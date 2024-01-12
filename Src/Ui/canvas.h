#ifndef Canvas_h
#define Canvas_h

#include "stmf4lib.h"
#include "frameBuffer.h"
#include "font.h"
#include "bitmap.h"
#include "stringUtils.h"
#include "dsp.h"

class Canvas {

public:

	enum Color {
		WHITE,
		LIGHT_GRAY,
		GRAY,
		DARK_GRAY,
		BLACK,
		INVERTED,
		SUBTRACTED,
		MULTIPLIED,
	};

	enum Allign {
		LEFT,
		RIGHT,
		CENTER,
		TOP,
		BOTTOM,
	};

	//Frame buffer
	static const int width_ = 256;
	static const int height_ = 64;
	const int width() { return Canvas::width_; }
	const int height() { return Canvas::height_; }

	FrameBuffer <width_, height_> buffer;


	void draw_pixel(int x, int y, Color color) {
		if (buffer.inside(x, y) == false) {
			return;
		}

		switch (color)
		{
		case WHITE:
			buffer.write(x, y, 0x00);
			break;
		case LIGHT_GRAY:
			buffer.write(x, y, 0x04);
			break;
		case GRAY:
			buffer.write(x, y, 0x07);
			break;
		case DARK_GRAY:
			buffer.write(x, y, 0x0C);
			break;
		case BLACK:
			buffer.write(x, y, 0x0F);
			break;
		case INVERTED:
			buffer.write(x, y, buffer.read(x, y) ^ 0xFF);
			break;
		case SUBTRACTED:
			buffer.write(x, y, buffer.read(x, y) / 3);
			break;
		case MULTIPLIED:
			buffer.write(x, y, stmlib::clip_max(0xF, buffer.read(x, y) * 3));
			break;
		default:
			break;
		}
	}

	void horizontal_line(int x, int y, int w, Color color) {
		int x2 = x + w;
		for (int xi = x; xi < x2; ++xi) {
			draw_pixel(xi, y, color);
		}
	}

	void vertical_line(int x, int y, int h, Color color) {
		int y2 = y + h;
		for (int yi = y; yi < y2; ++yi) {
			draw_pixel(x, yi, color);
		}
	}

	void fill(int x, int y, int w, int h, Color color) {
		int y2 = y + h;
		for (int yi = y; yi < y2; ++yi) {
			horizontal_line(x, yi, w, color);
		}
	}

	void frame(int x, int y, int w, int h, Color color, int border = 1) {
		int x2 = stmlib::clip_min(0, x + w - 1);
		int y2 = stmlib::clip_min(0, y + h - 1);

		for (int i = 0; i < border; ++i) {
			horizontal_line(x, y + i, w, color);
			horizontal_line(x, y2 - i, w, color);
			vertical_line(x + i, y, h, color);
			vertical_line(x2 - i, y, h, color);
		}
	}

	void box(int x, int y, int w, int h, Color frame_clr, Color fill_clr, int border = 1){
		frame(x, y, w, h, frame_clr, border);
		fill(x + border, y + border, w - (border * 2), h - (border * 2), fill_clr);
	}

	void get_xy_allignment(int *x, int *y, int w, int h, int frame_w, int frame_h, Allign x_allign, Allign y_allign) {
		int x_ = *x;
		int y_ = *y;

		switch (x_allign)
		{
		case LEFT:
			break;
		case CENTER:
			x_ += (w - frame_w) / 2;
			break;
		case RIGHT:
			x_ += (w - frame_w);
			break;
		default:
			break;
		}

		switch (y_allign)
		{
		case TOP:
			break;
		case CENTER:
			y_ += (h - frame_h) / 2;
			break;
		case BOTTOM:
			y_ += (h - frame_h);
			break;
		default:
			break;
		}

		*x = stmlib::clip(0, width() - frame_w, x_);
		*y = stmlib::clip(0, height() - frame_h, y_);
	}

	// bitmap
	void set_bitmap(Bitmap::Id id, Color color = BLACK) {
		bitmap_color = color;
		bitmap.set(id);
	}

	// text
	void set_font(Font::Type type, Color color = BLACK) {
		font_color = color;
		font.set_type(type);
	}

	int text_cursor(){
		return text_cursor_;
	}

	void draw_text(int x, int y, const char *str, Color color = BLACK) {
		if (str) {
			font_color = color;
			while (*str) {
				draw_char(x, y, *str++);
				x = text_cursor();
			}
		}
	}

	void draw_text(int x, int y, int w, int h, const char *str, Allign x_allign, Allign y_allign, Color color = BLACK) {
		if (str) {
			int x_ = x;
			int y_ = y;
			get_xy_allignment(&x_, &y_, w, h, font.string_width(str), font.height(), x_allign, y_allign);
			draw_text(x_, y_, str, color);
		}
	}

	void draw_bitmap(int x, int y, int w, int h, Bitmap::Id id, Allign x_allign, Allign y_allign) {
		int x_ = x;
		int y_ = y;
		set_bitmap(id);
		get_xy_allignment(&x_, &y_, w, h, bitmap.width, bitmap.height, x_allign, y_allign);
		draw_bitmap(x_, y_, id);
	}

	void draw_char(int x, int y, char c);
	void draw_bitmap(int x, int y, Bitmap::Id id, int frame = 0);

private:
	int text_cursor_ = 0;
	Color font_color = BLACK;
	Color bitmap_color = BLACK;
};

extern Canvas canvas;

#endif
