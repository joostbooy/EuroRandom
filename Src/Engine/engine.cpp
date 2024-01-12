#include "engine.h"
#include "usb.h"

Engine engine;

void Engine::init() {

}


/*	Engine commands */

void Engine::start() {

}

void Engine::stop() {

}

void Engine::suspend() {

}

void Engine::resume() {

}

/*	Tasks */

void Engine::process_requests() {

}

// 8 Khz interrupt
void Engine::tick() {

}

// low priority
void Engine::process() {

}

float Engine::processing_time() {
	return (1.f / 500.f) * processing_time_;
}

// 2 khz interrupt
void Engine::update() {
	uint32_t start = micros.read();

	//

	processing_time_ = micros.read() - start;
}
