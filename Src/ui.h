#ifndef Ui_h
#define Ui_h

#include "que.h"

class Ui {

public:

	enum Type {
		BUTTON,
		GATE,
	};

	void init();
	void poll();
	void process();

private:
	struct Event {
		Type type;
		int id;
	};
	Que<Event, 16>event_que;
};

#endif
