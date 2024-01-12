#ifndef TextBufferPainter_h
#define TextBufferPainter_h

#include "canvas.h"
#include "window.h"
#include "StringBuilder.h"

class TextBufferPainter {

public:

	static void clear() {
		entries = 0;
		top_row = 0;
		for (int i = 0; i < kMaxRows; ++i) {
			text[i].clear();
		}
	}

	static void write(const char* text_) {
		text[entries % kMaxRows].write(text_);

		++entries;
		if (entries >= kMaxRows) {
			top_row = (entries - kMaxRows) % kMaxRows;
		}
	}

	static void draw() {
		canvas.set_font(Font::SMALL);

		for (int i = 0; i < kMaxRows; ++i) {
			int text_row = (top_row + i) % kMaxRows;
			cell = window.cell(0, i);
			canvas.draw_text(cell.x, cell.y, cell.w, cell.h, text[text_row].read(), Canvas::LEFT, Canvas::CENTER);
		}
	}

private:

	static int entries;
	static int top_row;
	static const int kMaxRows = 6;

	static Window window;
	static Window::Cell cell;

	static StringBuilderBase<32>text[kMaxRows];
};

#endif
