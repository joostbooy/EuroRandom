#ifndef Controller_h
#define Controller_h

#include "stmf4lib.h"

#define SERIAL_ID(collumn, row) ((collumn * 8) + row)

class Controller {

public:

	enum Id {
		// step encoders
		STEP_ENC_1				= SERIAL_ID(0, 4),
		STEP_ENC_2				= SERIAL_ID(2, 4),
		STEP_ENC_3				= SERIAL_ID(4, 4),
		STEP_ENC_4				= SERIAL_ID(6, 4),
		STEP_ENC_5				= SERIAL_ID(8, 4),
		STEP_ENC_6				= SERIAL_ID(10, 4),
		STEP_ENC_7				= SERIAL_ID(12, 4),
		STEP_ENC_8				= SERIAL_ID(14, 4),
		STEP_ENC_9				= SERIAL_ID(1, 4),
		STEP_ENC_10				= SERIAL_ID(3, 4),
		STEP_ENC_11				= SERIAL_ID(5, 4),
		STEP_ENC_12				= SERIAL_ID(7, 4),
		STEP_ENC_13				= SERIAL_ID(9, 4),
		STEP_ENC_14				= SERIAL_ID(11, 4),
		STEP_ENC_15				= SERIAL_ID(13, 4),
		STEP_ENC_16				= SERIAL_ID(15, 4),
		// step encoders push
		STEP_ENC_PUSH_1			= SERIAL_ID(0, 6),
		STEP_ENC_PUSH_2			= SERIAL_ID(2, 6),
		STEP_ENC_PUSH_3			= SERIAL_ID(4, 6),
		STEP_ENC_PUSH_4			= SERIAL_ID(6, 6),
		STEP_ENC_PUSH_5			= SERIAL_ID(8, 6),
		STEP_ENC_PUSH_6			= SERIAL_ID(10, 6),
		STEP_ENC_PUSH_7			= SERIAL_ID(12, 6),
		STEP_ENC_PUSH_8			= SERIAL_ID(14, 6),
		STEP_ENC_PUSH_9			= SERIAL_ID(1, 6),
		STEP_ENC_PUSH_10		= SERIAL_ID(3, 6),
		STEP_ENC_PUSH_11		= SERIAL_ID(5, 6),
		STEP_ENC_PUSH_12		= SERIAL_ID(7, 6),
		STEP_ENC_PUSH_13		= SERIAL_ID(9, 6),
		STEP_ENC_PUSH_14		= SERIAL_ID(11, 6),
		STEP_ENC_PUSH_15		= SERIAL_ID(13, 6),
		STEP_ENC_PUSH_16		= SERIAL_ID(15, 6),
		// step buttons
		STEP_BUTTON_1			= SERIAL_ID(0, 7),
		STEP_BUTTON_2			= SERIAL_ID(2, 7),
		STEP_BUTTON_3			= SERIAL_ID(4, 7),
		STEP_BUTTON_4			= SERIAL_ID(6, 7),
		STEP_BUTTON_5			= SERIAL_ID(8, 7),
		STEP_BUTTON_6			= SERIAL_ID(10, 7),
		STEP_BUTTON_7			= SERIAL_ID(12, 7),
		STEP_BUTTON_8			= SERIAL_ID(14, 7),
		STEP_BUTTON_9			= SERIAL_ID(1, 7),
		STEP_BUTTON_10			= SERIAL_ID(3, 7),
		STEP_BUTTON_11			= SERIAL_ID(5, 7),
		STEP_BUTTON_12			= SERIAL_ID(7, 7),
		STEP_BUTTON_13			= SERIAL_ID(9, 7),
		STEP_BUTTON_14			= SERIAL_ID(11, 7),
		STEP_BUTTON_15			= SERIAL_ID(13, 7),
		STEP_BUTTON_16			= SERIAL_ID(15, 7),
		// state
		PLAY_BUTTON				= SERIAL_ID(4, 0),
		STOP_BUTTON				= SERIAL_ID(6, 0),
		RECORD_BUTTON			= SERIAL_ID(8, 0),
		// mode
		SHIFT_BUTTON			= SERIAL_ID(0, 3),
		GROUP_BUTTON			= SERIAL_ID(0, 0),
		MUTE_BUTTON				= SERIAL_ID(2, 0),
		SOLO_BUTTON				= SERIAL_ID(2, 3),
		// utility
		COPY_BUTTON				= SERIAL_ID(15, 3),
		PASTE_BUTTON			= SERIAL_ID(15, 0),
		CLEAR_BUTTON			= SERIAL_ID(13, 3),
		DELETE_BUTTON			= SERIAL_ID(13, 0),
		SAVE_BUTTON				= SERIAL_ID(11, 0),
		// menu
		EDIT_BUTTON				= SERIAL_ID(9, 0),
		MENU_ENC				= SERIAL_ID(9, 1),
		MENU_ENC_PUSH			= SERIAL_ID(9, 3),
		X_ENC					= SERIAL_ID(4, 1),
		X_ENC_PUSH				= SERIAL_ID(4, 3),
		Y_ENC					= SERIAL_ID(11, 1),
		Y_ENC_PUSH				= SERIAL_ID(11, 3),
		// chapters
		SONG_CHAPTER_BUTTON		= SERIAL_ID(12, 0),
		TRACK_CHAPTER_BUTTON	= SERIAL_ID(10, 0),
		PATTERN_CHAPTER_BUTTON	= SERIAL_ID(10, 3),
		MIDI_CHAPTER_BUTTON		= SERIAL_ID(5, 0),
		CV_CHAPTER_BUTTON		= SERIAL_ID(7, 0),
		SYSTEM_CHAPTER_BUTTON	= SERIAL_ID(7, 3),
	};


	void init();
	void on_encoder(uint8_t id);
	void on_button(uint8_t id, bool state);
	bool is_pressed(uint8_t id);

	uint8_t curr_touched_encoder() {
		return curr_touched_encoder_;
	}

	uint8_t prev_touched_encoder() {
		return prev_touched_encoder_;
	}

	int8_t button_to_function(uint8_t id) {
		switch (id)
		{
		case STEP_BUTTON_7:		return 0;
		case STEP_BUTTON_8:		return 1;
		case STEP_BUTTON_9:		return 2;
		case STEP_BUTTON_10:	return 3;
		default:				return -1;
			break;
		}
	}

	int8_t encoder_to_function(uint8_t id) {
		switch (id)
		{
		case STEP_ENC_7:	return 0;
		case STEP_ENC_8:	return 1;
		case STEP_ENC_9:	return 2;
		case STEP_ENC_10:	return 3;
		default:			return -1;
			break;
		}
	}

	int8_t button_to_step(uint8_t id) {
		switch (id)
		{
		case STEP_BUTTON_1:		return 0;
		case STEP_BUTTON_2:		return 1;
		case STEP_BUTTON_3:		return 2;
		case STEP_BUTTON_4:		return 3;
		case STEP_BUTTON_5:		return 4;
		case STEP_BUTTON_6:		return 5;
		case STEP_BUTTON_7:		return 6;
		case STEP_BUTTON_8:		return 7;
		case STEP_BUTTON_9:		return 8;
		case STEP_BUTTON_10:	return 9;
		case STEP_BUTTON_11:	return 10;
		case STEP_BUTTON_12:	return 11;
		case STEP_BUTTON_13:	return 12;
		case STEP_BUTTON_14:	return 13;
		case STEP_BUTTON_15:	return 14;
		case STEP_BUTTON_16:	return 15;
		default:				return -1;
			break;
		}
	}

	int8_t encoder_to_step(uint8_t id) {
		switch (id)
		{
		case STEP_ENC_1:	return 0;
		case STEP_ENC_2:	return 1;
		case STEP_ENC_3:	return 2;
		case STEP_ENC_4:	return 3;
		case STEP_ENC_5:	return 4;
		case STEP_ENC_6:	return 5;
		case STEP_ENC_7:	return 6;
		case STEP_ENC_8:	return 7;
		case STEP_ENC_9:	return 8;
		case STEP_ENC_10:	return 9;
		case STEP_ENC_11:	return 10;
		case STEP_ENC_12:	return 11;
		case STEP_ENC_13:	return 12;
		case STEP_ENC_14:	return 13;
		case STEP_ENC_15:	return 14;
		case STEP_ENC_16:	return 15;
		default:			return -1;
			break;
		}
	}

	int8_t encoder_push_to_step(uint8_t id) {
		switch (id)
		{
		case STEP_ENC_PUSH_1:	return 0;
		case STEP_ENC_PUSH_2:	return 1;
		case STEP_ENC_PUSH_3:	return 2;
		case STEP_ENC_PUSH_4:	return 3;
		case STEP_ENC_PUSH_5:	return 4;
		case STEP_ENC_PUSH_6:	return 5;
		case STEP_ENC_PUSH_7:	return 6;
		case STEP_ENC_PUSH_8:	return 7;
		case STEP_ENC_PUSH_9:	return 8;
		case STEP_ENC_PUSH_10:	return 9;
		case STEP_ENC_PUSH_11:	return 10;
		case STEP_ENC_PUSH_12:	return 11;
		case STEP_ENC_PUSH_13:	return 12;
		case STEP_ENC_PUSH_14:	return 13;
		case STEP_ENC_PUSH_15:	return 14;
		case STEP_ENC_PUSH_16:	return 15;
		default:				return -1;
			break;
		}
	}

	bool encoder_is_pressed(uint8_t encoder_id) {
		switch (encoder_id)
		{
		case X_ENC:			return is_pressed(X_ENC_PUSH);
		case Y_ENC:			return is_pressed(Y_ENC_PUSH);
		case MENU_ENC:		return is_pressed(MENU_ENC_PUSH);
		case STEP_ENC_1:	return is_pressed(STEP_ENC_PUSH_1);
		case STEP_ENC_2:	return is_pressed(STEP_ENC_PUSH_2);
		case STEP_ENC_3:	return is_pressed(STEP_ENC_PUSH_3);
		case STEP_ENC_4:	return is_pressed(STEP_ENC_PUSH_4);
		case STEP_ENC_5:	return is_pressed(STEP_ENC_PUSH_5);
		case STEP_ENC_6:	return is_pressed(STEP_ENC_PUSH_6);
		case STEP_ENC_7:	return is_pressed(STEP_ENC_PUSH_7);
		case STEP_ENC_8:	return is_pressed(STEP_ENC_PUSH_8);
		case STEP_ENC_9:	return is_pressed(STEP_ENC_PUSH_9);
		case STEP_ENC_10:	return is_pressed(STEP_ENC_PUSH_10);
		case STEP_ENC_11:	return is_pressed(STEP_ENC_PUSH_11);
		case STEP_ENC_12:	return is_pressed(STEP_ENC_PUSH_12);
		case STEP_ENC_13:	return is_pressed(STEP_ENC_PUSH_13);
		case STEP_ENC_14:	return is_pressed(STEP_ENC_PUSH_14);
		case STEP_ENC_15:	return is_pressed(STEP_ENC_PUSH_15);
		case STEP_ENC_16:	return is_pressed(STEP_ENC_PUSH_16);
		default:			return false;
			break;
		}
	}

private:
	uint32_t pressed[(16 * 8) / 32];
	uint8_t curr_touched_encoder_;
	uint8_t prev_touched_encoder_;
};

extern Controller controller;

#endif
