#ifndef Ui_h
#define Ui_h

#include "stmf4lib.h"
#include "que.h"

class Ui {

public:
	enum ControlType {
		BUTTON,
		ENCODER
	};

	struct Event {
		Ui::ControlType type;
		uint8_t id;
		int8_t value;
	};

	void init();
	void poll();
	void process();
	void clear_que();
	void send_display();

private:
	uint32_t last_interval = 0;
	uint32_t display_interval = 0;
	uint8_t sw_raw[8 * 16];
};

extern Ui ui;

#endif
