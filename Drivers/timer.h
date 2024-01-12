#ifndef Timer_h
#define Timer_h

#include "stmf4lib.h"

class Timer {

public:
	void start_2(uint32_t freq);
	void start_3(uint32_t freq);
	void start_4(uint32_t freq);

private:

};

extern Timer timer;

#endif
