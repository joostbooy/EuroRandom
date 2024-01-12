#ifndef Pages_h
#define Pages_h

#include "stmf4lib.h"
#include "StringBuilder.h"

class Pages {

public:

	enum Id {
		TOP_PAGE,
		NUM_OF_PAGES
	};

	struct EventHandlers {
		void(*init)();
		void(*enter)();
		void(*exit)();
		void(*msTick)(uint16_t);
		void(*drawLeds)();
		void(*drawDisplay)();
		void(*onEncoder)(uint8_t, int);
		void(*onButton)(uint8_t, uint8_t);
		const uint16_t (*targetFps)();
	};

	void init();
	void msTick(uint16_t);
	void drawLeds();
	void drawDisplay();
	void onEncoder(uint8_t, int);
	void onButton(uint8_t, uint8_t);
	uint16_t targetFps();

	uint8_t top();
	uint8_t bottom();
	uint8_t num_open();
	void move_to_top(Id page);

	void open(Id page);
	bool is_open(Id page);
	void close(Id page) ;
	void close_all();

private:
	uint8_t curr_page_;

};

extern Pages pages;

#endif
