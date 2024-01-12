#include "controller.h"

Controller controller;

void Controller::init() {
	prev_touched_encoder_ = 0;
	curr_touched_encoder_ = 0;
	for (int i = 0; i < (16 * 8) / 32; ++i) {
		pressed[i] = 0;
	}
}

void Controller::on_encoder(uint8_t id) {
	if (id != curr_touched_encoder_) {
		prev_touched_encoder_ = curr_touched_encoder_;
		curr_touched_encoder_ = id;
	}
}

void Controller::on_button(uint8_t id, bool state) {
	uint8_t index = id / 32;
	uint32_t mask = 1 << (id & 31);
	pressed[index] &= ~(mask);
	if (state) {
		pressed[index] |= mask;
	}
}

bool Controller::is_pressed(uint8_t id) {
	uint8_t index = id / 32;
	uint32_t mask = 1 << (id & 31);
	return pressed[index] & mask;
}
