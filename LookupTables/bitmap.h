#ifndef Bitmap_h
#define Bitmap_h

#include "stmf4lib.h"

class Bitmap {

public:

	enum Id {
		PLACEHOLDER_PAGE,
		MIDI_IN_PAGE,
		MIDI_OUT_PAGE,
		CV_IN_PAGE,
		CV_OUT_PAGE,
		PROJECT_LOAD_PAGE,
		PROJECT_SAVE_PAGE,
		SONG_PAGE,
		SONG_MONITOR_PAGE,
		SETTINGS_PAGE,
		PATTERN_PAGE,
		TRACK_PAGE,
		WARNING_ICON,
		TIMER,

		NUM_OF_BITMAPS
	};

	const uint8_t* data;
	uint8_t width;
	uint8_t height;
	uint8_t frames;

	void set(Id id);
	const uint8_t* pointer(uint8_t);

private:

};

extern Bitmap bitmap;

#endif
