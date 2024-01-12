#include "TextBufferPainter.h"


int TextBufferPainter::entries = 0;
int TextBufferPainter::top_row = 0;
const int TextBufferPainter::kMaxRows;


StringBuilderBase<32>TextBufferPainter::text[kMaxRows];

Window TextBufferPainter::window = {
	.x = 0,
	.y = 12,
	.width = canvas.width(),
	.height = canvas.height() - 24,
	.collumns = 1,
	.rows = kMaxRows,
};

Window::Cell TextBufferPainter::cell;
