#ifndef Entry_h
#define Entry_h

#include "ff.h"
#include "stringUtils.h"

// entry's corresponding to the directory set in directory.h

class Entry {

public:

	enum Filter {
		NONE,
		PROJECT,
		CALIBRATION,
		FOLDER
	};

	struct List {
		StringBuilderBase<16>name;
		uint32_t size;
		bool is_dir;
	};

	static const int kMaxListSize = 8;
	List list[kMaxListSize];


	void init(DIR* dir_, FILINFO* fil_info_, StringBuilder* dir_path_) {
		dir = dir_;
		fil_info = fil_info_;
		dir_path = dir_path_;
	}

	bool is_dir() {
		return fil_info->fattrib & AM_DIR;
	}

	bool is_read_only() {
		return fil_info->fattrib & AM_RDO;
	}

	bool is_archive() {
		return fil_info->fattrib & AM_ARC;
	}

	bool has_extension(const char* extension) {
		return StringUtils::has_extension(name(), extension);
	}

	const char* name() {
		return fil_info->fname;
	}

	uint32_t size() {
		return fil_info->fsize;
	}

	const char* path() {
		return path_.write(dir_path->read(), "/", name());
	}

	const char* path(const char* entry_name) {
		return path_.write(dir_path->read(), "/", entry_name);
	}

	bool is_visible() {
		if ((fil_info->fattrib & AM_HID) || (fil_info->fattrib & AM_SYS)) {
			return false;
		}

		switch (filter)
		{
		case NONE:
			return true;
		case FOLDER:
			return is_dir();
		case PROJECT:
			return is_dir() || has_extension(".PRJ");
		case CALIBRATION:
			return is_dir() || has_extension(".CAL");
		default:
			break;
		}

		return false;
	}

	bool rename(const char* old_name, const char* new_name) {
		const char* old_path = buffer.write(dir_path->read(), "/", old_name);
		const char* new_path = path_.write(dir_path->read(), "/", new_name);
		return f_rename(old_path, new_path) == FR_OK;
	}

	bool excists(const char* name) {
		return f_stat(path(name), fil_info) == FR_OK;
	}

	const char* generate_duplicate_name(const char* name) {
		const int kMaxTries = 100;

		buffer.write(name);
		if (excists(buffer.read()) == false) {
			return buffer.read();
		}

		for (int i = 2; i < kMaxTries; ++i) {
			buffer.write(i, "_", name);
			if (excists(buffer.read()) == false) {
				return buffer.read();
			}
		}
		return "\0";
	}

	void rewind() {
		f_rewinddir(dir);
	}

	bool next() {
		return (f_readdir(dir, fil_info) == FR_OK) && (fil_info->fname[0] != '\0');
	}

	bool next_visible() {
		while (next()) {
			if (is_visible()) {
				return true;
			}
		}
		return false;
	}

	void set_list_filter(Filter filter_) {
		filter = filter_;
	}

	int num_visible() {
		int num_entries = 0;

		rewind();

		while (next_visible() && (num_entries < 32767)) {
			++num_entries;
		}
		return num_entries;
	}

	int num_visible_files() {
		int num_entries = 0;

		rewind();

		while (next_visible() && (num_entries < 32767)) {
			if (is_dir() == false) {
				++num_entries;
			}
		}
		return num_entries;
	}

	void make_list(int offset, int size) {
		list_size_ = 0;

		if (size > kMaxListSize) {
			size = kMaxListSize;
		}

		rewind();

		while (offset && next_visible()) {
			--offset;
		}

		int i = 0;
		while (next_visible() && size--) {
			list[i].name.write(fil_info->fname);
			list[i].size = fil_info->fsize;
			list[i].is_dir = fil_info->fattrib & AM_DIR;
			++i;
		}
		list_size_ = i;
	}

	int list_size() {
		return list_size_;
	}

	List* read_list(int idx) {
		return idx >= list_size_ ? nullptr : &list[idx];
	}

	void reset() {
		list_size_ = 0;
		filter = NONE;
	}

private:
	DIR* dir;
	FILINFO* fil_info;
	StringBuilder* dir_path;
	StringBuilderBase<64>path_;
	StringBuilderBase<64>buffer;
	int list_size_ = 0;
	Filter filter = NONE;
};

#endif
