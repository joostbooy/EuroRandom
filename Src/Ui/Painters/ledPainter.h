#ifndef LedPainter_h
#define LedPainter_h

#include "ui.h"
#include "matrix.h"
#include "engine.h"

class LedPainter {

public:

	static void clear() {
		matrix.clear_leds();
	}

	static void set_shift(Matrix::LedColor color) {
		matrix.set_led(0, 0, color);
	}

	static void set_group(Matrix::LedColor color) {
		matrix.set_led(0, 1, color);
	}

	static void set_solo(Matrix::LedColor color) {
		matrix.set_led(1, 0, color);
	}

	static void set_mute(Matrix::LedColor color) {
		matrix.set_led(1, 1, color);
	}


	static void set_play(Matrix::LedColor color) {
		matrix.set_led(3, 0, color);
	}

	static void set_stop(Matrix::LedColor color) {
		matrix.set_led(4, 1, color);
	}

	static void set_record(Matrix::LedColor color) {
		matrix.set_led(5, 1, color);
	}


	static void set_edit(Matrix::LedColor color) {
		matrix.set_led(2, 5, color);
	}

	static void set_menu(Matrix::LedColor color) {
		matrix.set_led(3, 5, color);
	}

	static void set_save(Matrix::LedColor color) {
		matrix.set_led(4, 4, color);
	}


	static void set_x(Matrix::LedColor color) {
		matrix.set_led(2, 1, color);
	}

	static void set_y(Matrix::LedColor color) {
		matrix.set_led(5, 5, color);
	}


	static void set_paste(Matrix::LedColor color) {
		matrix.set_led(6, 4, color);
	}

	static void set_copy(Matrix::LedColor color) {
		matrix.set_led(6, 5, color);
	}

	static void set_delete(Matrix::LedColor color) {
		matrix.set_led(7, 4, color);
	}

	static void set_clear(Matrix::LedColor color) {
		matrix.set_led(7, 5, color);
	}


	static void set_step_button(int step, Matrix::LedColor color) {
		matrix.set_led(step_button_leds[step].x, step_button_leds[step].y, color);
	}

	static void set_step_encoder(int step, Matrix::LedColor color) {
		matrix.set_led(step_encoder_leds[step].x, step_encoder_leds[step].y, color);
	}

	static void set_clock_position(int position) {
		for (int i = 0; i < 16; ++i) {
			Matrix::LedColor color = (i == position) ? Matrix::RED : Matrix::BLACK;
			set_step_encoder(i, color);
		}
	}

	static void footer_buttons(uint8_t num_active) {
		for (int i = 0; i < 16; ++i) {
			Matrix::LedColor color = Matrix::BLACK;
			if ((i >= 6) && (i <= 9) && ((i - 6) < num_active)) {
				color = Matrix::GREEN;
			}
			set_step_button(i, color);
		}
	}

	static void footer_buttons(Matrix::LedColor c1, Matrix::LedColor c2, Matrix::LedColor c3, Matrix::LedColor c4) {
		Matrix::LedColor colors[4] = {c1, c2, c3, c4};

		for (int i = 0; i < 16; ++i) {
			Matrix::LedColor color = Matrix::BLACK;
			if (i >= 6 && i <= 9) {
				color = colors[i - 6];
			}
			set_step_button(i, color);
		}
	}

	static void footer_encoders(uint8_t num_active) {
		for (int i = 0; i < 16; ++i) {
			Matrix::LedColor color = Matrix::BLACK;
			if ((i >= 6) && (i <= 9) && ((i - 6) < num_active)) {
				color = Matrix::GREEN;
			}
			set_step_encoder(i, color);
		}
	}

	static void footer_encoders(Matrix::LedColor c1, Matrix::LedColor c2, Matrix::LedColor c3, Matrix::LedColor c4) {
		Matrix::LedColor colors[4] = {c1, c2, c3, c4};

		for (int i = 0; i < 16; ++i) {
			Matrix::LedColor color = Matrix::BLACK;
			if (i >= 6 && i <= 9) {
				color = colors[i - 6];
			}
			set_step_encoder(i, color);
		}
	}

private:
	struct Map {
		const uint8_t x;
		const uint8_t y;
	};

	static Map chapter_leds[6];
	static Map step_button_leds[16];
	static Map step_encoder_leds[16];
};

#endif
