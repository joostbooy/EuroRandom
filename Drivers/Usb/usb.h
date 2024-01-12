#ifndef Usb_h
#define Usb_h

#include "stmf4lib.h"
#include "tusb.h"

class Usb {

public:

	void init();

	// only call from main, not safe to call in a ISR
	// https://github.com/hathach/tinyusb/issues/52
	void task() {
		tud_task();
	}

	bool read(uint8_t data[4]) {
		return tud_midi_packet_read(data);
	}

	bool write(uint8_t data[4]) {
		return tud_midi_packet_write(data);
	}

	bool write_byte(uint8_t byte) {
		data_[1] = byte;
		return write(data_);
	}

private:
	uint8_t data_[4] { 0x0F, 0x00, 0x00, 0x00 };
};

extern Usb usb;

#endif
