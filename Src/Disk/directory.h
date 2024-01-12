#ifndef Directory_h
#define Directory_h

#include "ff.h"
#include "stringBuilder.h"

class Directory {

public:

	void init(DIR* dir_, int root_id_, FRESULT* result_) {
		dir = dir_;
		root_id = root_id_;
		result = result_;
		path.write(root_id, ":");
	}

	StringBuilder* path_ptr() {
		return &path;
	}

	uint8_t max_path_length() {
		return kMaxPathLength;
	}

	const char* read_path() {
		const char* curr_path = path.read();
		return buffer.write(curr_path);
	}

	bool open_path(const char* path_) {
		const char* new_path_ = build_new_path(path_);
		if (f_opendir(dir, new_path_) == FR_OK) {
			path.write(new_path_);
			return true;
		}
		return false;
	}

	bool close() {
		return f_closedir(dir) == FR_OK;
	}

	const char* root() {
		return buffer.write(root_id, ":");
	}

	bool has_root(const char* path_) {
		return (path_[0] == (root_id + 48)) && (path_[1] == ':');
	}

	bool is_root() {
		const char* text = path.read();
		return has_root(text) && (text[2] == '\0');
	}

	bool reset() {
		close();
		path.write(root());
		return f_opendir(dir, path.read()) == FR_OK;
	}

	bool reopen() {
		return f_opendir(dir, path.read()) == FR_OK;
	}

	bool enter(const char* dir_name) {
		const char* old_path = path.read();

		buffer.write(old_path);
		buffer.append("/");
		buffer.append(dir_name);

		return open_path(buffer.read());
	}

	bool exit() {
		const char* old_path = path.read();
		uint8_t length = path.length();

		if (is_root()) {
			return 0;
		}

		old_path += (length - 1);

		while (length--) {
			if (*old_path-- == '/') {
				old_path = path.read();

				buffer.write(old_path);
				buffer.truncate(length);
				return open_path(buffer.read());
			}
		}
		return 0;
	}

	bool make(const char* dir_name) {
		buffer.write(path.read(), "/", dir_name);
		return f_mkdir(buffer.read()) == FR_OK;
	}

	bool remove(const char* dir_name) {
		buffer.write(path.read(), "/", dir_name);
		return f_unlink(buffer.read()) == FR_OK;
	}

private:
	DIR* dir;
	FRESULT* result;
	uint8_t root_id;

	static const uint8_t kMaxPathLength = 64;
	StringBuilderBase<64>path;			// the current valid path
	StringBuilderBase<64>new_path;		// buffer to build new path, used only in build_new_path()
	StringBuilderBase<64>buffer;		// general text buffer


	const char* build_new_path(const char* path_) {
		new_path.write(path_);

		if (has_root(new_path.read()) == false) {
			new_path.prepend(root());
		}

		// remove extension
		int pos = 0;
		path_ = new_path.read();

		while (*path_ != '.') {
			if (*path_++ == '\0') {
				return new_path.read();
			}
			++pos;
		}
		new_path.truncate(pos);
		return new_path.read();
	}

};

#endif
