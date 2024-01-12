#ifndef MidiInputPage_h
#define MidiInputPage_h

#include "topPage.h"
#include "midiInputUiList.h"
#include "monitorPage.h"

namespace MidiInputPage {
	//Declarations
	void init();
	void enter();
	void exit();
	void msTick(uint16_t ticks);
	void drawDisplay();
	void updateLeds();
	void onButton(uint8_t id, uint8_t state);
	void onEncoder(uint8_t id, int inc);
	const uint16_t targetFps();

	//variables
	MidiInputUiList midiInputUiList;

	enum FooterOptions {
		MONITOR,
		NUM_FOOTER_OPTIONS
	};

	const char* const footer_text[NUM_FOOTER_OPTIONS] = { "MONITOR" };

	void clear_settings() {
		settings.midiInput(midiInputUiList.selected_port()).init();
	}

	void init() {

	}

	void enter() {
		ListPage::set_clear_callback(&clear_settings);
		ListPage::set_list(&midiInputUiList);
		ListPage::enter();
	}

	void exit() {
		ListPage::exit();
	}

	void onEncoder(uint8_t id, int inc) {
		ListPage::onEncoder(id, inc);
	}

	void onButton(uint8_t id, uint8_t state) {
		ListPage::onButton(id, state);

		switch (controller.button_to_function(id))
		{
		case MONITOR:
			if (state) {
				MonitorPage::set_port(MonitorPage::MIDI_IN, midiInputUiList.selected_port());
				pages.open(Pages::MONITOR_PAGE);
			}
			break;
		default:
			break;
		}
	}

	void drawLeds() {
		ListPage::drawLeds();
		LedPainter::footer_buttons(NUM_FOOTER_OPTIONS);
	}

	void msTick(uint16_t ticks) {
		ListPage::msTick(ticks);
	}

	// Bottom to top
	void drawDisplay() {
		ListPage::drawDisplay();
		LedPainter::set_step_encoder(midiInputUiList.selected_port(), Matrix::GREEN);
		WindowPainter::draw_footer(footer_text, NUM_FOOTER_OPTIONS);
	}

	const uint16_t targetFps() {
		return 1000 / 16;
	}

	const Pages::EventHandlers eventHandlers = {
		&init,
		&enter,
		&exit,
		&msTick,
		&drawLeds,
		&drawDisplay,
		&onEncoder,
		&onButton,
		&targetFps,
	};

};

#endif
