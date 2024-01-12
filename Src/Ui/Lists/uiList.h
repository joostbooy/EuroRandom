#ifndef UiList_h
#define UiList_h

#include "uiText.h"

class UiList {

public:

	enum Mode {
		SELECT,
		EDIT
	};

	Mode mode() {
		return mode_;
	}

	void set_mode(Mode mode) {
		mode_ = mode;
	}

	int selected_item() {
		return selected_item_;
	}

	void select_item(int item) {
		selected_item_ = stmlib::clip(0, num_items() - 1, item);
	}

	void on_click() {
		if (mode() == SELECT) {
			set_mode(EDIT);
		} else {
			set_mode(SELECT);
		}
	}

	void on_encoder(int inc, bool shifted) {
		if (mode_ == SELECT) {
			select_item(selected_item() + inc);
		} else {
			edit(selected_item(), inc, shifted);
		}
	}

	virtual const int num_items();
	virtual const char* item_text(int item);
	virtual const char* value_text(int item);
	virtual void edit(int item, int inc, bool shifted);

private:
	Mode mode_ = SELECT;
	int selected_item_ = 0;
};

#endif
