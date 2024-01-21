#include "ui.h"

void Ui::init() {

}

void Ui::poll() {
	//event_que.write({BUTTON, 1});
}

void Ui::process() {
	while (event_que.readable()) {
		//Event e = event_que.read();
	}
}
