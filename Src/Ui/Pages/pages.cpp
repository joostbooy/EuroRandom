#include "pages.h"
#include "stack.h"
#include "topPage.h"


Pages pages;
Stack <uint8_t, 8> page_stack;

const Pages::EventHandlers* eventHandlers[Pages::NUM_OF_PAGES] = {
	[Pages::TOP_PAGE]				= &TopPage::eventHandlers,
};

void Pages::init() {
	page_stack.clear();
	for (uint8_t i = 0; i < Pages::NUM_OF_PAGES; ++i) {
		eventHandlers[i]->init();
	}
}

uint8_t Pages::num_open(){
	return page_stack.size();
}

uint8_t Pages::top() {
	uint8_t size = page_stack.size();
	if (size > 0) {
		return page_stack.read(size - 1);
	} else {
		return TOP_PAGE;
	}
}

uint8_t Pages::bottom() {
	uint8_t size = page_stack.size();
	if (size > 0) {
		return page_stack.read(0);
	} else {
		return TOP_PAGE;
	}
}

// this does not call page->enter() it only moves the page
void Pages::move_to_top(Id page) {
	if (curr_page_ != page) {
		page_stack.remove_value(page);
		if (page_stack.writeable()) {
			page_stack.push(page);
			curr_page_ = page;
		}
	}
}

bool Pages::is_open(Id page){
	if (page_stack.find(page) >= 0) {
		return true;
	}
	return false;
}

void Pages::open(Id page) {
	if ((!is_open(page)) && page_stack.writeable()) {
		page_stack.push(page);
		eventHandlers[page]->enter();
		curr_page_ = top();
	}
}

void Pages::close(Id page) {
	int8_t idx = page_stack.find(page);
	if (idx >= 0) {
		page_stack.remove_indexed(idx);
		eventHandlers[page]->exit();
		curr_page_ = top();
	}
}

void Pages::close_all() {
	while (page_stack.readable()) {
		uint8_t page = page_stack.pop();
		eventHandlers[page]->exit();
	}
	curr_page_ = TOP_PAGE;
}


// Events
void Pages::drawDisplay() {
	for (uint8_t i = 0; i < page_stack.size(); ++i) {
		uint8_t page = page_stack.read(i);
		eventHandlers[page]->drawDisplay();
	}
	eventHandlers[TOP_PAGE]->drawDisplay();
}

void Pages::msTick(uint16_t ticks) {
	for (uint8_t i = 0; i < page_stack.size(); ++i) {
		uint8_t page = page_stack.read(i);
		eventHandlers[page]->msTick(ticks);
	}
	eventHandlers[TOP_PAGE]->msTick(ticks);
}

void Pages::drawLeds() {
	for (uint8_t i = 0; i < page_stack.size(); ++i) {
		uint8_t page = page_stack.read(i);
		eventHandlers[page]->drawLeds();
	}
	eventHandlers[TOP_PAGE]->drawLeds();
}

void Pages::onEncoder(uint8_t id, int inc){
	eventHandlers[curr_page_]->onEncoder(id, inc);
	eventHandlers[TOP_PAGE]->onEncoder(id, inc);
}

void Pages::onButton(uint8_t id, uint8_t state){
	eventHandlers[curr_page_]->onButton(id, state);
	eventHandlers[TOP_PAGE]->onButton(id, state);
}

uint16_t Pages::targetFps() {
	return eventHandlers[curr_page_]->targetFps();
}
