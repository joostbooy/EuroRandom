#include "ui.h"
#include "que.h"
#include "display.h"
#include "controller.h"
#include "matrix.h"
#include "canvas.h"
#include "pages.h"

Ui ui;

Que<Ui::Event, 16> ui_que;

static const int num_enc_rows = 2;
static const int num_buttons_rows = 4;
static const int enc_a_rows[num_enc_rows] = { 1, 4 };
static const int enc_b_rows[num_enc_rows] = { 2, 5 };
static const int buttons_rows[num_buttons_rows] = { 0, 3, 6, 7 };

void addEvent(Ui::ControlType type, uint8_t id, int8_t value)  {
	Ui::Event e;
	e.type = type;
	e.id = id;
	e.value = value;
	ui_que.write(e);
}

void Ui::init() {
	last_interval = 0;
	display_interval = 0;
	controller.init();
	pages.init();
	ui_que.clear();
}

void Ui::poll() {
	uint8_t reading[16];
	matrix.refresh(&reading[0]);

	for (int x = 0; x < 16; ++x) {
		for (int y = 0; y < 8; ++y) {
			uint8_t sw = y + (x * 8);
			sw_raw[sw] <<= 1;
			if (reading[x] & (1 << y)) {
				sw_raw[sw] |= 1;
			}
		}
	}

	for (int x = 0; x < 16 * 8; x += 8) {
		for (int y = 0; y < num_buttons_rows; ++y) {
			uint8_t button = buttons_rows[y] + x;
			if (sw_raw[button] == 0x80) {
				addEvent(Ui::BUTTON, button, 1);
			} else if (sw_raw[button] == 0x01) {
				addEvent(Ui::BUTTON, button, 0);
			}
		}

		for (int y = 0; y < num_enc_rows; ++y) {
			uint8_t a = enc_a_rows[y] + x;
			uint8_t b = enc_b_rows[y] + x;
			if ((sw_raw[b] & 0x03) == 0x02 && (sw_raw[a] & 0x03) == 0x00) {
				addEvent(Ui::ENCODER, a, 1);
			} else if ((sw_raw[a] & 0x03) == 0x02 && (sw_raw[b] & 0x03) == 0x00) {
				addEvent(Ui::ENCODER, a, -1);
			}
		}
	}
}

void Ui::process() {
	while (ui_que.readable()) {
		Ui::Event e = ui_que.read();
		switch (e.type)
		{
		case Ui::BUTTON:
			controller.on_button(e.id, e.value);
			pages.onButton(e.id, e.value);
			break;
		case Ui::ENCODER:
			controller.on_encoder(e.id);
			pages.onEncoder(e.id, e.value);
			break;
		default:
			break;
		}
	}

	uint32_t interval = (micros.read() / 1000) - last_interval;

	if (interval >= 1) {
		last_interval += interval;
		pages.msTick(interval);
		matrix.lock_leds();
		matrix.clear_leds();
		pages.drawLeds();
		matrix.unlock_leds();
	}

	display_interval += interval;
	if (display_interval >= pages.targetFps()) {
		send_display();
	}
}

void Ui::send_display() {
	while (display.dma_busy());
	display_interval = 0;
	canvas.buffer.clear();
	pages.drawDisplay();
	display.sendBuffer(canvas.buffer.data(), canvas.buffer.size());
}

void Ui::clear_que() {
	ui_que.clear();
}
