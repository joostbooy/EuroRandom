#include "ledPainter.h"

LedPainter::Map LedPainter::step_encoder_leds[16] = {
	{ .x = 0, .y = 2 },
	{ .x = 1, .y = 2 },
	{ .x = 2, .y = 2 },
	{ .x = 3, .y = 2 },
	{ .x = 4, .y = 2 },
	{ .x = 5, .y = 2 },
	{ .x = 6, .y = 2 },
	{ .x = 7, .y = 2 },
	{ .x = 0, .y = 6 },
	{ .x = 1, .y = 6 },
	{ .x = 2, .y = 6 },
	{ .x = 3, .y = 6 },
	{ .x = 4, .y = 6 },
	{ .x = 5, .y = 6 },
	{ .x = 6, .y = 6 },
	{ .x = 7, .y = 6 },
};

LedPainter::Map LedPainter::step_button_leds[16] = {
	{ .x = 0, .y = 3 },
	{ .x = 1, .y = 3 },
	{ .x = 2, .y = 3 },
	{ .x = 3, .y = 3 },
	{ .x = 4, .y = 3 },
	{ .x = 5, .y = 3 },
	{ .x = 6, .y = 3 },
	{ .x = 7, .y = 3 },
	{ .x = 0, .y = 7 },
	{ .x = 1, .y = 7 },
	{ .x = 2, .y = 7 },
	{ .x = 3, .y = 7 },
	{ .x = 4, .y = 7 },
	{ .x = 5, .y = 7 },
	{ .x = 6, .y = 7 },
	{ .x = 7, .y = 7 },
};

LedPainter::Map LedPainter::chapter_leds[6] = {
	{ .x = 6, .y = 0 },	// song
	{ .x = 7, .y = 0 },	// track
	{ .x = 7, .y = 1 },	// pattern
	{ .x = 0, .y = 4 },	// midi
	{ .x = 0, .y = 5 },	// cv
	{ .x = 1, .y = 5 },	// system
};
