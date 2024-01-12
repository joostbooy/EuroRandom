#ifndef Window_h
#define Window_h


class Window {

public:

	const int x;
	const int y;
	const int width;
	const int height;
	const int collumns;
	const int rows;
	const int coll_width = width / collumns;
	const int row_height = height / rows;

	struct Cell {
		int x, y, w, h;
	};

	struct Axis {
		int first;
		int last;
		int max_visible;
		int items_total;
		bool scrollable;
	};

	Cell cell_ = {
		.x = 0,
		.y = 0,
		.w = coll_width,
		.h = row_height
	};

	Axis row_ = {
		.first = 0,
		.last = rows - 1,
		.max_visible = rows,
		.items_total = rows,
		.scrollable = false
	};

	Axis coll_ = {
		.first = 0,
		.last = collumns - 1,
		.max_visible = collumns,
		.items_total = collumns,
		.scrollable = false
	};

	Axis &row() {
		return row_;
	}

	Axis &coll() {
		return coll_;
	}

	Cell &cell(int _col, int _row) {
		cell_.x = x + ((_col - coll_.first) * coll_width);
		cell_.y = y + ((_row - row_.first) * row_height);
		return cell_;
	}

	void scroll_to_row(int index) {
		scroll_to(row_, index);
	}

	void scroll_to_collumn(int index) {
		scroll_to(coll_, index);
	}

	void set_row_items_total(int total) {
		set_items_total(row_, total, rows);
	}

	void set_coll_items_total(int total) {
		set_items_total(coll_, total, collumns);
	}

private:

	inline void scroll_to(Axis &a, int index) {
		int index_ = stmlib::clip(0, a.items_total - 1, index);

		if (index_ > a.last) {
			a.last = index_;
			a.first = a.last - (a.max_visible - 1);
		} else if (index_ < a.first) {
			a.first = index_;
			a.last = a.first + (a.max_visible - 1);
		}
	}

	inline void set_items_total(Axis &a, int total, int max) {
		a.items_total = total;

		if (a.items_total > max) {
			a.max_visible = max;
			a.scrollable = true;
		} else {
			a.max_visible = total;
			a.scrollable = false;
		}

		a.first = 0;
		a.last = a.max_visible - 1;
	}
};

#endif
